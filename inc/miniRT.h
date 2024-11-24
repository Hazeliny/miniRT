/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:56:02 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/24 22:43:24 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "handle_errors.h"

# define WINX 560
# define WINY 560

typedef struct s_point
{
    float   x;
    float   y;
    float   z;
}   t_point;

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}   t_rgb;

typedef struct s_obj
{
    char    typ[2];
    void    *elm;
}   t_obj;

typedef struct s_al
{
    float   ratio;
    t_rgb   *color;
}   t_al;

typedef struct s_cam
{
    t_point *pov; // point of view
    t_point *n_vec;
    int     fov; // field of view
}   t_cam;

typedef struct s_lit
{
    t_point *l_src;
    float   r_brt;
    t_rgb   *color;
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


#endif
