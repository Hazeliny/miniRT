/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:49:01 by linyao            #+#    #+#             */
/*   Updated: 2025/01/06 16:12:28 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

float   light_dot(t_intersect *i, t_lit *lit)
{
    t_vec3  ipos;
    t_vec3  nor;
    float   res;

    ipos = i_pos(i);
    nor = get_normal_inter(i);
    ipos = vec3_sub(&ipos, &lit->l_src);
    normalize(&ipos);
    res = vec3_dot(&nor, &ipos);
    if (res < 0)
        res = -res;
    return (res);
}

t_rgb   specular(t_intersect *i, t_lit *lit)
{
    t_rgb   rgb;
    t_vec3  ipos;
    t_vec3  normal;
    float   dot;

    rgb = (t_rgb){200, 200, 200};
    ipos = i_pos(i);
    normal = get_normal_inter(i);
    ipos = vec3_sub(&ipos, &(lit->l_src));
    ipos = vec3_sum(ipos, i->ray.direction);
    normalize(&ipos);
    dot = vec3_dot(&normal, &ipos);
    if (dot < 0)
        return (density(&rgb, 0));
    return (density(&rgb, pow(dot, 100)));
}

void    update_ray_color(t_rgb (*rgb)[2], t_rt *rt, t_point *p, t_rgb *ds)
{
    if (!p->y && !p->z)
    {
        (*rgb)[1] = mpl_color(rt->al.color, *ds);
        p->y = 1;
    }
}

t_rgb   light_color(t_rgb (*rgb)[2], t_rt *rt, t_intersect *i, t_point *p)
{
    t_rgb   ds;
    t_lit   *lit;

    apply_checkerboard(i, rgb);
    apply_bump(i);
    apply_texture(i);
    lit = rt->lit;
    while (lit)
    {
        p->x = light_dot(i, lit);
        ds = density(&lit->color, lit->r_brt * p->x);
        if (p->x <= 0)
            return ((*rgb)[0]);
        if (in_shadow(i, rt->obj, lit))
            update_ray_color(rgb, rt, p, &ds);
        else
        {
            p->z = 1;
            (*rgb)[1] = sum_color(sum_color(mpl_color(ds, (*rgb)[0]), \
                                specular(i, lit)), (*rgb)[1]);
        }
        lit = lit->next;
    }
    return ((*rgb)[1]);
}