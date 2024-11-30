/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:12:31 by linyao            #+#    #+#             */
/*   Updated: 2024/11/29 15:24:00 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_rgb   specular(t_intersect *i, t_lit *lit)
{
    t_rgb   rgb;
    t_vec3  ipos;
    t_vec3  normal;
    float   dot;

    rgb = (t_rgb){200, 200, 200};
    ipos = i_pos(i);
    normal = get_normal_inter(i);
    ipos = vec3_sub(&(lit->l_src), &ipos);
    ipos = vec3_sum(ipos, i->ray.direction);
    normalize(&ipos);
    dot = vec3_dot(&normal, &ipos);
    if (dot < 0)
        return (density(&rgb, 0));
    return (density(&rgb, pow(dot, 100)));
}

void    update_ray_color(t_rgb *rgb[2], t_rt *rt, t_point *p, t_rgb *ds)
{
    if (!p->y && !p->z)
    {
        *(rgb[1]) = mpl_color(rt->al.color, *ds);
        p->y = 1;
    }
}

t_rgb   light_color(t_rgb *rgb[2], t_rt *rt, t_intersect *i, t_point *p)
{
    t_rgb   ds;

    p->x = light_dot(i, &rt->lit);
    ds = density(&rt->lit.color, rt->lit.r_brt * p->x);
    if (p->x <= 0)
        return (*(rgb[0]));
    if (in_shadow(i, rt->obj, &rt->lit))
        update_ray_color(rgb, rt, p, &ds);
    else
    {
        p->z = 1;
        *(rgb[1]) = sum_color(sum_color(mpl_color(ds, *(rgb[0])), \
                                specular(i, &rt->lit)), *(rgb[1]));
    }
    return (*(rgb[1]));
}

t_rgb   color_intersect(t_rt *rt, t_intersect *i, t_obj *obj)
{
    t_rgb   rgb[2];
    t_rgb   res;
    t_pl    *pl;
    t_sp    *sp;
    t_cy    *cy;
    t_point p;

    if (obj->typ[0] == 'p' && obj->typ[1] == 'l')
    {
        pl = (t_pl *)obj->elm;
        rgb[0] = sum_color(rt->al.color, pl->rgb);
        rgb[1] = density(&pl->rgb, 0.0f);
    }
    else if (obj->typ[0] == 's' && obj->typ[1] == 'p')
    {
        sp = (t_sp *)obj->elm;
        rgb[0] = sum_color(rt->al.color, sp->rgb);
        rgb[1] = density(&sp->rgb, 0.0f);

    }
    else if (obj->typ[0] == 'c' && obj->typ[1] == 'y')
    {
        cy = (t_cy *)obj->elm;
        rgb[0] = sum_color(rt->al.color, cy->rgb);
        rgb[1] = density(&cy->rgb, 0.0f);
    }
    else
        return ((t_rgb){0, 0, 0});
    p = init_point(0, 0, 0);
    res = light_color(&rgb, rt, i, &p);
    return (res);
}