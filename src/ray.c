/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:12:31 by linyao            #+#    #+#             */
/*   Updated: 2024/12/25 18:38:24 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static void    base_rgb_pl(t_rt *rt, t_pl *pl, t_rgb rgb[2])
{
    rgb[0] = sum_color(rt->al.color, pl->rgb);//to combine ambient light (rt->al.color) with the object's color (obj->rgb)
    rgb[1] = density(&pl->rgb, 0.0f);//to initialize a zero-dense color for later calculations
}

static void    base_rgb_sp(t_rt *rt, t_sp *sp, t_rgb rgb[2])
{
    rgb[0] = sum_color(rt->al.color, sp->rgb);
    rgb[1] = density(&sp->rgb, 0.0f);
}

static void    base_rgb_cy(t_rt *rt, t_cy *cy, t_rgb rgb[2])
{
    rgb[0] = sum_color(rt->al.color, cy->rgb);
    rgb[1] = density(&cy->rgb, 0.0f);
}

//to calculate the color of the intersected object based on the ray intersection and the object's material properties
t_rgb   color_intersect(t_rt *rt, t_intersect *i, t_obj *obj)
{
    t_rgb   rgb[2];
    t_rgb   res;
    t_point p;

//Distinguishes the object type (pl, sp, cy) and assigns base colors
    if (obj->typ[0] == 'p' && obj->typ[1] == 'l')
        base_rgb_pl(rt, (t_pl *)obj->elm, rgb);
    else if (obj->typ[0] == 's' && obj->typ[1] == 'p')
        base_rgb_sp(rt, (t_sp *)obj->elm, rgb);
    else if (obj->typ[0] == 'c' && obj->typ[1] == 'y')
        base_rgb_cy(rt, (t_cy *)obj->elm, rgb);
    else
        return ((t_rgb){0, 0, 0});
    p = init_point(0, 0, 0);
    res = light_color(&rgb, rt, i, &p);//to compute lighting at the intersection point
    return (res);
}