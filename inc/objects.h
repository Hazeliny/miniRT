/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:57:24 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/25 22:24:34 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "miniRT.h"

typedef struct s_pl
{
    t_point p;
    t_vec3  n_vec;
    t_rgb   rgb;
    t_vec3  normal;
}   t_pl;

typedef struct s_sp
{
    t_point *center;
    float   radius;
    t_rgb   rgb;
}   t_sp;

typedef struct s_cy
{
    t_point *center;
    t_vec3  *axis;
    t_obj   *topcap;
    t_obj   *bottcap;
    float   radius;
    float   hgt;
    t_rgb   rgb;
}   t_cy;

#endif
