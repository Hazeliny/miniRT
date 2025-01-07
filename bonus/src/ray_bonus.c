/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:12:31 by linyao            #+#    #+#             */
/*   Updated: 2025/01/08 00:22:11 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

static void    base_rgb_pl(t_rt *rt, t_pl *pl, t_rgb rgb[2])
{
    rgb[0] = sum_color(rt->al.color, pl->rgb);
    rgb[1] = density(&pl->rgb, 0.0f);
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

static void    base_rgb_cn(t_rt *rt, t_cn *cn, t_rgb rgb[2])
{
    rgb[0] = sum_color(rt->al.color, cn->rgb);
    rgb[1] = density(&cn->rgb, 0.0f);
}

//t_rgb   color_intersect(t_rt *rt, t_intersect *i, t_obj *obj, t_view *view)
t_rgb   color_intersect(t_rt *rt, t_intersect *i, t_obj *obj)
{
    t_rgb   rgb[2];
    t_rgb   res;
    t_point p;

    if (obj->typ[0] == 'p' && obj->typ[1] == 'l')
        base_rgb_pl(rt, (t_pl *)obj->elm, rgb);
    else if (obj->typ[0] == 's' && obj->typ[1] == 'p')
    {
        base_rgb_sp(rt, (t_sp *)obj->elm, rgb);
//        if (i->shape->has_texture)
//            i->shape->h = compute_half_vector(i, view);
    }
    else if (obj->typ[0] == 'c' && obj->typ[1] == 'y')
        base_rgb_cy(rt, (t_cy *)obj->elm, rgb);
    else if (obj->typ[0] == 'c' && obj->typ[1] == 'n')
        base_rgb_cn(rt, (t_cn *)obj->elm, rgb);
    else
        return ((t_rgb){0, 0, 0});
    p = init_point(0, 0, 0);
    res = light_color(&rgb, rt, i, &p);
    return (res);
}