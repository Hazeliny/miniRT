/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:56:02 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 00:10:42 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include "../minilibx_linux/mlx.h"
//# include "../../minilibx_macos/mlx.h"
# include "../lib/libft/get_next_line.h"
# include "../lib/libft/libft.h"
# include "handle_errors_bonus.h"
# include "control_bonus.h"

/*==========================		Macros			=========================*/

# define TRUE 1
# define FALSE 0

# define WINX 960
# define WINY 680



# define T_VALUE_MAX 1.0e6
# define T_VALUE_MIN 0.00001
# define EPSILON 1e-6
# define FLT_MAX 3.402823e+38

# define YES_UPDATE 1
# define NO_UPDATE 0

# define TOP    0
# define BOTTOM 1

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
	struct s_obj	*shape;
	t_ray   ray;
	t_point pos;
	t_vec3  nor;
	float   t;
}	t_intersect;

typedef struct s_bitmap
{
	void	*img;
	int		bitpixel;
	int		linesize;
	int		endian;
	char	*buffer;
	char	*path;
	int		width;
	int		height;
	int		addr_incr;
	int		antialiasing_on;
}		t_bitmap;

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
	int (*is_intersect)(t_intersect *i, struct s_obj *obj, int f);
	int (*update_inter)(t_intersect *i, struct s_obj *obj, float t_val);
}   t_vtable;

typedef struct s_obj
{
	char			typ[3];
	void            *elm;
	t_vtable        *vtable;
	bool            has_checkerboard;
	bool has_bump;
	t_bitmap bump;
	float bump_f;
	t_bitmap texture;
	bool has_texture;
	float texture_f;
//	float alpha;
	t_vec3 h;
	t_vec3 lx;
	t_vec3 ly;
	t_vec3 lz;
	struct s_obj    *next;
}   t_obj;

typedef struct s_pl
{
    t_point p;
    t_vec3  n_vec;
    t_rgb   rgb;
    t_vec3  normal;
	t_vec3  u_dir;
	t_vec3  v_dir;
	float	tile_scale;
}   t_pl;

typedef struct s_sp
{
    t_point center;
    float   radius;
    t_rgb   rgb;
}   t_sp;

typedef struct s_cy
{
    t_point center;
    t_vec3  axis;
    t_obj   *top;
    t_obj   *bottom;
    float   radius;
    float   hgt;
    t_rgb   rgb;
}   t_cy;

typedef struct s_cn
{
	t_vec3	apex;
    t_vec3	center;
	t_vec3	axis;
	bool	has_caps;
	t_obj	*bottom;
    float	hgt;
    float	radius;
    float	angle;
	t_vec3	normal;
    t_rgb   rgb;
}   t_cn;

typedef struct s_al
{
	float   ratio;
	t_rgb   color;
}   t_al;

typedef struct s_cam
{
	t_point pov;
	t_vec3	n_vec;
	int     fov;
	t_bitmap	*bm;
	struct s_cam    *next;
	struct s_cam    *prev;
}   t_cam;

typedef struct s_lit
{
	t_point l_src;
	float   r_brt;
	t_rgb   color;
	struct s_lit    *next;
}   t_lit;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		axis_x;
	int		axis_y;
}	t_mlx;

typedef struct s_control
{
	bool	mouse_l;
	bool	mouse_r;
	bool	keyctrl;
}	t_control;

typedef struct	s_event
{
	int		key_ctrl;
	int		key_shift;
	int		btn_l;
	int		btn_m;
	int		btn_r;
}	t_event;

typedef struct s_rt
{
    t_mlx       frm;
    t_bitmap    bitmap;
	t_control	ctrl;
	t_event		event;
	t_vec3		coord;
    t_al    al;
    t_cam   *cam;
    t_lit   *lit;
    t_obj   *obj;
	int		n_al;
	int		n_cam;
	int		n_lit;
}   t_rt;

/*=======================		Ray tracing functions		======================*/

void	parse(t_rt *rt, const char *file_name);
int 	exit_program(void *para);
int		press_key(int key, void *para);
t_bitmap    *create_bitmap(t_mlx *mlx);
int		render_rt(t_rt *rt);
void    render(t_rt *rt);
void    ray_trace(t_rt *rt, t_cam *cam);
int		sp_intersect(t_intersect *i, t_obj *obj, int f);
int		sp_update_inter(t_intersect *i, t_obj *obj, float t_val);
int		pl_intersect(t_intersect *i, t_obj *obj, int f);
int		pl_update_inter(t_intersect *i, t_obj *obj, float t_val);
int		cy_intersect(t_intersect *i, t_obj *obj, int f);
int		cy_update_inter(t_intersect *i, t_obj *obj, float t_val);
int 	check_cy_topbottom(t_intersect *i, t_cy *cy, float *a);
int		cn_intersect(t_intersect *i, t_obj *obj, int f);
int		cn_update_inter(t_intersect *i, t_obj *obj, float t_val);
//int		i_cn_apex(t_intersect *i, t_cn *cn, t_ray *ray);
int		i_cn_bottom(t_intersect *i, t_cn *cn, float *a);
//int		i_cn_bottom(t_intersect *i, t_cn *cn, t_ray *ray);
t_view  create_view(t_cam *cam);
t_ray   create_ray(t_view *view, t_vec3 vec);
bool    obj_intersect(t_intersect *i, t_obj **obj);
t_rgb   light_color(t_rgb (*rgb)[2], t_rt *rt, t_intersect *i, t_point *p);
t_vec3  i_pos(t_intersect *i);
float   light_dot(t_intersect *i, t_lit *lit);
bool    in_shadow(t_intersect *i, t_obj *obj, t_lit *lit);
int check_shadow(t_intersect *i, t_obj *obj, t_ray *ray);
int rgb_toi(t_rgb rgb);
//t_rgb   color_intersect(t_rt *rt, t_intersect *i, t_obj *obj, t_view *view);
t_rgb   color_intersect(t_rt *rt, t_intersect *i, t_obj *obj, t_view *view);
t_rgb   specular(t_intersect *i, t_lit *lit);
void    update_ray_color(t_rgb (*rgb)[2], t_rt *rt, t_point *p, t_rgb *ds);
void    write_pixel(t_bitmap *bm, int color, int x, int y);


/*=====================			Math formulas		=====================*/

t_vec3  vec3_sub(t_point *p1, t_point *p2);
t_vec3  vec3_sum(t_vec3 v1, t_vec3 v2);
t_vec3  vec3_mpl(t_vec3 v1, float num);
float   vec3_dot(t_vec3 *v1, t_vec3 *v2);
t_vec3  vec3_cross(t_vec3 v1, t_vec3 v2);
void	normalize(t_vec3 *nor);
t_vec3  normalize_axis(t_cn *cn);
t_vec3  planarize(float x, float y);
t_rgb   sum_color(t_rgb rgb1, t_rgb rgb2);
t_rgb   mpl_color(t_rgb rgb1, t_rgb rgb2);
t_rgb   density(t_rgb *rgb, float dense);
t_vec3  get_normal_inter(t_intersect *i);
t_vec3  get_cynormal(t_cy *cy, t_vec3 pos);
t_vec3  get_plnormal(t_vec3 vec);
t_vec3	get_spnormal(t_sp *sp, t_vec3 vec);
t_vec3  get_cnnormal(t_cn *cn, t_vec3 vec);
float   vec3_sqr(t_vec3 v);
float   vec3_len(t_vec3 v);
int get_t(t_intersect *i, float *a);
int solve_quadratic(t_intersect *i, t_vec3 lorig, t_cy *cy, float a[4]);
float   sqr(float n);


/*=====================			Parsing functions		=====================*/

void	parse(t_rt *rt, const char *file_name);
int 	ft_isspace_str(char *s);
t_cam	*find_lstlast_cam(t_cam **cam);
t_lit	*find_lstlast_lit(t_lit **lit);
t_obj	*find_lstlast_obj(t_obj **obj);
int		check_filename(const char *fn);
void	read_map_file(t_rt *rt, const char *str);
void	decode_line(char *line, t_rt *rt);
int		verify_line_elem(char *line);
void	verify_id(char *s, char **ss, t_rt *rt);
void	*ft_calloc_new(size_t num, size_t size);
void	check_point(char *s);
void 	check_commas(char *s);
void    check_negative(char *s);
void    check_extreme(char *s);


/*=====================			Initialization		=====================*/

void    init_al(t_rt *rt, char **ss);
void    init_cam(t_rt *rt, char **ss);
void    init_lit(t_rt *rt, char **ss);
void    init_obj(t_obj **obj, char **str, const char *type);
t_sp	*init_sp(char **ss);
t_pl    *init_pl(char **ss);
t_cy    *init_cy(char **ss);
t_cn    *init_cn(char **ss);
void	init_vtable(t_obj *obj);
t_point init_point(float x, float y, float z);
t_rgb   init_rgb(int r, int g, int b);
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
t_obj   *init_surface(t_cy *cy, int surface);
void    check_al_ratio(char *s);
int		init_al_rgb(char *s, t_al *al);
void    init_cam_pov(char *s, t_cam *cam);
void    init_cam_nvec(char *s, t_cam *cam);
void    init_cam_fov(char *s, t_cam *cam);
void    init_lit_lsrc(char *s, t_lit *lit);
void    check_lit_rbrt(char *s);
void    init_lit_color(char *s, t_lit *lit);
void    init_cn_apex(char *s, t_cn *cn);
void    init_cn_axis(char *s, t_cn *cn);
t_obj   *init_cn_surface(t_cn *cn);
float   init_cn_float(char *s);
void    init_cn_rgb(char *s, t_cn *cn);


/*=====================			Checkerboard		=====================*/

void    init_checkerboard(t_obj **obj, char **str);
void    apply_checkerboard(t_intersect *i, t_rgb (*rgb)[2]);
void    init_pl_uv(t_pl *pl);
void    init_cb_scale(char *s, t_pl *pl);


/*=====================			Bump map		=====================*/

void init_bump(t_obj **obj, char **ss);
int validate_xpmfile(char *path);
void create_obj_norm(t_rt *rt);
void apply_bump(t_intersect *i);
void bump_on_sp(t_intersect *i, t_bitmap *bm, int grey_scale[3][2]);
void calculate_uv_sp(t_obj *obj, t_vec3 p, float *uv);
t_vec3 pertub_bump_nor(t_obj *obj, t_vec3 nor, float pu, float pv);

/*=====================			Texture map		=====================*/

void	init_texture(t_obj **obj, char **ss);
void	apply_texture(t_intersect *i, t_rgb (*rgb)[2]);
t_vec3 compute_half_vector(t_intersect *i, t_view *view);
t_rgb get_pixelcolor(t_bitmap *bm, float u, float v);
t_rgb   rgb_color(int rgb);
t_vec3  get_normal_from_texture(t_bitmap *bm, float uv[2]);
t_rgb   matting(t_intersect *i, t_lit *lit, t_rgb ds, t_rgb (*rgb)[2]);


/*=====================			Control		=====================*/

t_vec3  set_coord(float x, float y, float z);
void    init_event(t_rt *rt);
int press_mouse(int mouse, int x, int y, t_rt *rt);
int release_mouse(int mouse, int x, int y, t_rt *rt);


/*=====================			Free		=====================*/

void	free_array(char **arr);
void	free_sp(t_sp *sp);
void	free_pl(t_pl *pl);
void	free_cy(t_cy *cy);
void	free_cy_topbottom(t_obj *tb);
void	free_cn(t_cn *cn);
void	free_cn_bottom(t_obj *b);
void	free_obj(t_obj **objs);
void	free_rt(t_rt *rt);


#endif