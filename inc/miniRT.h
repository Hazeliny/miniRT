/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:56:02 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/25 21:52:14 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include "../minilibx_macos/mlx.h"
# include "../lib/libft/libft.h"
# include "handle_errors.h"
# include "objects.h"

# define WINX 960
# define WINY 680

# define T_VALUE_MAX 1.0e6
# define T_VALUE_MIN 0.00001
# define EPSILON 1e-5

# define YES_UPDATE 1
# define NO_UPDATE 0

# ifdef __APPLE__
#  define ESC 53
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
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define C 99
#  define V 118
# endif


typedef struct s_point
{
    float   x;
    float   y;
    float   z;
}   t_point;

typedef struct s_point   t_vec3;

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;

typedef struct s_ray
{
    t_point     *origin;
    t_vec3      *direction;
}   t_ray;

typedef struct s_intersect
{
    t_obj   *shape;
    t_ray   *ray;
    t_point *pos; // coordinate of intersection point
    t_vec3  nor; // normal vector
    float   t; // t value, scalar along with direction from ray origin, closest intersection coefficient
}   t_intersect;

typedef struct s_vtable
{
    int (*is_intersect)(t_intersect *i, void *elm, int f);
    void (*update_inter)(t_intersect *i, void *elm);
}   t_vtable;

typedef struct s_obj
{
    char            typ[2];
    void            *elm;
    t_vtable        *vtable;
    struct s_obj    *next;
}   t_obj;

typedef struct s_al
{
    float   ratio;
    t_rgb   *color;
}   t_al;

typedef struct s_cam
{
    t_point *pov; // point of view
    t_vec3  *n_vec;
    int     fov; // field of view
    t_bitmap    *bm;
}   t_cam;

typedef struct s_lit
{
    t_point *l_src;
    float   r_brt;
    t_rgb   *color;
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
    void    *mlx;
    void    *win;
}   t_mlx;

typedef struct s_rt
{
    t_mlx       frm;
    t_bitmap    bitmap;
    t_al    *al; //ambient light
    t_cam   *cam; //camera
    t_lit   *lit; //light
    t_obj   *obj; // plane, sphere, cylinder
}   t_rt;


void    parse(t_rt *rt, char **filepath);
int     exit_program(void *para);
int	    press_key(int key, void *para);
void    init_vtable(t_obj **obj);
int     render_rt(t_rt *rt);
int     sp_intersect(t_intersect *i, void *elm, int f);
void    sp_update_inter(t_intersect *i, void *elm);
int     pl_intersect(t_intersect *i, void *elm, int f);
void    pl_update_inter(t_intersect *i, void *elm);
int     cy_intersect(t_intersect *i, void *elm, int f);
void    cy_update_inter(t_intersect *i, void *elm);

/*=====================math=====================*/
t_vec3  vec3_sub(t_point *p1, t_point *p2);
float   vec3_dot(t_vec3 *v1, t_vec3 *v2);
t_vec3  normalize(t_vec3 *nor);

#endif
