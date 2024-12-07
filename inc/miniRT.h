/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:56:02 by mpietrza          #+#    #+#             */
/*   Updated: 2024/12/01 21:59:00 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h> //printf, perror
# include <stdlib.h> //malloc, free, exit
# include <unistd.h> //open, read, write, close
# include <stdbool.h>
# include <string.h> //strerror
# include <fcntl.h> //open
# include <math.h> // math like: sqrt, pow, M_PI, M_PI_2
# include <time.h> // time	
# include "../minilibx_linux/mlx.h" // minilibx
# include "../lib/libft/get_next_line.h" // get_next_line
# include "../lib/libft/libft.h" // libft functions
# include "handle_errors.h"
# include "objects.h"

/*==========================		Macros			=========================*/

# define TRUE 1
# define FALSE 0

# define WINX 960
# define WINY 680



# define T_VALUE_MAX 1.0e6
# define T_VALUE_MIN 0.00001
# define EPSILON 1e-6
# define M_PI 3.14159265358979323846

# define YES_UPDATE 1
# define NO_UPDATE 0

# ifdef __APPLE__
#  define ESC 53
#  define Q 12
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define C 8
#  define V 9
#  define KeyPress 2
#  define KeyPressMask (1L<<0)
#  define DestroyNotify 17
#  define StructureNotifyMask (1L<<17)
# else
#  define ESC 65307
#  define Q 113
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define C 99
#  define V 118
# endif

/*=====================		Structures definitions		====================*/

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
}	t_point;

typedef struct s_point	t_vec3;

typedef struct s_rgb
{
	int r;
	int g;
	int b;
}   t_rgb;

typedef struct s_ray
{
	t_point     origin;
	t_vec3      direction;
	float		t_max;
}   t_ray;

typedef struct s_intersect
{
	t_obj   *shape;
	t_ray   ray;
	t_point *pos; // coordinate of intersection point
	t_vec3  nor; // normal vector
	float   t; // t value, scalar along with direction from ray origin, closest intersection coefficient
}	t_intersect;

typedef struct s_view
{
	t_point	source;
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;
	float	h;
	float	w;
}	t_view;

typedef struct s_vtable
{
	int (*is_intersect)(t_intersect *i, void *elm, int f);
	int (*update_inter)(t_intersect *i, void *elm, float t_val);
}   t_vtable;

typedef struct s_obj
{
	char			typ[3];
	void            *elm;
	t_vtable        *vtable;
	struct s_obj    *next;
}   t_obj;

typedef struct s_al
{
	float   ratio;
	t_rgb   color;
}   t_al;

typedef struct s_cam
{
	t_point pov; // point of view
	t_vec3	n_vec;
	int     fov; // field of view
	t_bitmap	*bm;
}   t_cam;

typedef struct s_lit
{
	t_point l_src;
	float   r_brt;
	t_rgb   color;
	struct s_lit    *next;
}   t_lit;

typedef struct s_bitmap
{
	void	*img;
	int		bitpixel;
	int		linesize;
	int		endian;
	char	*buffer;
}		t_bitmap;


typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_rt
{
    t_mlx       frm;
    t_bitmap    bitmap;
    t_al    al; //ambient light
    t_cam   cam; //camera
    t_lit   lit; //light
    t_obj   *obj; // plane, sphere, cylinder
	int		n_al;
	int		n_cam;
	int		n_lit;
}   t_rt;

/*=======================		Ray tracing functions		======================*/

void	parse(t_rt *rt, const char *file_name);
int 	exit_program(void *para);
int		press_key(int key, void *para);
int		render_rt(t_rt *rt);
int		sp_intersect(t_intersect *i, void *elm, int f);
int		sp_update_inter(t_intersect *i, void *elm, float t_val);
int		pl_intersect(t_intersect *i, void *elm, int f);
int		pl_update_inter(t_intersect *i, void *elm, float t_val);
int		cy_intersect(t_intersect *i, void *elm, int f);
int		cy_update_inter(t_intersect *i, void *elm, float t_val);
int 	check_cy_topbottom(t_intersect *i, t_cy *cy, float *a);
t_view  create_view(t_cam *cam);
t_ray   create_ray(t_view *view, t_vec3 vec);
t_rgb   light_color(t_rgb *rgb[2], t_rt *rt, t_intersect *i, t_point *p);
t_vec3  i_pos(t_intersect *i);
float   light_dot(t_intersect *i, t_lit *lit);
bool    in_shadow(t_intersect *i, t_obj *obj, t_lit *lit);
int check_shadow(t_intersect *i, t_obj *obj, t_ray *ray);
int rgb_toi(t_rgb rgb);
t_rgb   color_intersect(t_rt *rt, t_intersect *i, t_obj *obj);
t_rgb   specular(t_intersect *i, t_lit *lit);
void    update_ray_color(t_rgb *rgb[2], t_rt *rt, t_point *p, t_rgb *ds);
void    write_pixel(t_bitmap *bm, int color, int x, int y);


/*=====================			Math formulas		=====================*/

t_vec3  vec3_sub(t_point *p1, t_point *p2);
t_vec3  vec3_sum(t_vec3 v1, t_vec3 v2);
t_vec3  vec3_mpl(t_vec3 v1, float num);
float   vec3_dot(t_vec3 *v1, t_vec3 *v2);
t_vec3  vec3_cross(t_vec3 v1, t_vec3 v2);
t_vec3  normalize(t_vec3 *nor);
t_vec3  planarize(float x, float y);
t_rgb   sum_color(t_rgb rgb1, t_rgb rgb2);
t_rgb   mpl_color(t_rgb rgb1, t_rgb rgb2);
t_rgb   density(t_rgb *rgb, float dense);
t_vec3  get_normal_inter(t_intersect *i);
t_vec3  get_cynormal(t_cy *cy, t_vec3 pos);
t_vec3  get_plnormal(t_vec3 vec);
float   vec3_sqr(t_vec3 v);
float   vec3_len(t_vec3 v);
int get_tValue(t_intersect *i, float *a);
int solve_quadratic(t_intersect *i, t_vec3 lorig, t_cy *cy, float a[4]);


/*=====================			Parsing functions		=====================*/

void	parse(t_rt *rt, const char *file_name);
int 	ft_isspace(char *s);
float	ft_atof(const char *str);
t_obj	*find_lstlast(t_obj **obj);
int		check_filename(char *fn);
void	read_map_file(t_rt *rt, char *str);
void	decode_line(char *line, t_rt *rt);
int		verify_line_elem(char *line);
void	verify_id(char *s, char **ss, t_rt *rt);


/*=====================			Initialization		=====================*/

void    init_al(t_rt *rt, char **ss);
void    init_cam(t_rt *rt, char **ss);
void    init_lit(t_rt *rt, char **ss);
void    init_obj(t_obj **obj, char **str, const char *type);
t_sp	*init_sp(char **ss);
t_pl    *init_pl(char **ss);
t_cy    *init_cy(char **ss);
void    init_vtable(t_obj **obj);
t_point init_point(float x, float y, float z);
t_rgb   init_rgb(int r, int g, int b);
t_obj	*find_lstlast(t_obj **obj);
void    init_sp_center(char *s, t_sp *sp);
void    init_sp_radius(char *s, t_sp *sp);
void    init_sp_rgb(char *s, t_sp *sp);
void    init_pl_p(char *s, t_pl *pl);
void    init_pl_n_vec(char *s, t_pl *pl);
void    init_pl_rgb(char *s, t_pl *pl);
void    init_cy_center(char *s, t_cy *cy);
void    init_cy_axis(char *s, t_cy *cy);
float	init_cy_float(char *s);
void    init_cy_rgb(char *s, t_cy *cy);
t_obj   init_surface(t_cy *cy, int surface);
void    check_al_ratio(char *s);
int		init_al_rgb(char *s, t_al *al);
void    init_cam_pov(char *s, t_cam *cam);
void    init_cam_nvec(char *s, t_cam *cam);
void    init_cam_fov(char *s, t_cam *cam);
void    init_lit_lsrc(char *s, t_lit *lit);
void    check_lit_rbrt(char *s);
void    init_lit_color(char *s, t_lit *lit);


/*=====================			Free		=====================*/

void	free_array(char **arr);
void	free_sp(t_sp *sp);
void	free_pl(t_pl *pl);
void	free_cy(t_cy *cy);
void	free_obj(t_obj *obj);
void	free_rt(t_rt *rt);


#endif