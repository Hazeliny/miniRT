/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:00:21 by linyao            #+#    #+#             */
/*   Updated: 2025/01/06 16:38:55 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

int pl_intersect(t_intersect *i, t_obj *obj, int f)
{
    t_pl    *pl;
    float   dot_dir_nor;
    float   proj_dist;
    float   t_val;
    t_vec3  tmp;
    
    pl = (t_pl *)obj->elm;
    dot_dir_nor = vec3_dot(&i->ray.direction, &pl->normal);
    tmp = vec3_sub(&i->ray.origin, &pl->p);
    proj_dist = vec3_dot(&tmp, &pl->normal);
    if (!dot_dir_nor || (dot_dir_nor > 0 && proj_dist > 0))
        return (0);
    t_val = -proj_dist / dot_dir_nor;
    if (t_val <= T_VALUE_MIN || t_val >= i->t)
        return (0);
    if (f == YES_UPDATE)
        pl_update_inter(i, obj, t_val);
    return (1);
}

int pl_update_inter(t_intersect *i, t_obj *obj, float t_val)
{
    i->t = t_val;
    i->shape = (t_obj *)obj;
    i->pos = vec3_sum(i->ray.origin, vec3_mpl(i->ray.direction, i->t));
    i->nor = ((t_pl *)(i->shape->elm))->normal;
    normalize(&i->nor);
    return (1);
}

t_vec3  get_plnormal(t_vec3 vec)
{
    t_vec3  nor;

    normalize(&vec);
    nor = vec3_cross(vec, vec3_cross(planarize(0, 1), vec));
    if (!nor.x && !nor.y && !nor.z)
        nor.x = 1;
    normalize(&nor);
    return (nor);
}

void    init_pl_uv(t_pl *pl)
{
    t_vec3  arbitrary_vec;

    if (fabs(pl->normal.x) < 0.9)
        arbitrary_vec = (t_vec3){1, 0, 0};
    else
        arbitrary_vec = (t_vec3){0, 1, 0};
    pl->u_dir = vec3_cross(arbitrary_vec, pl->normal);
    normalize(&(pl->u_dir));
    pl->v_dir = vec3_cross(pl->normal, pl->u_dir);
    normalize(&(pl->v_dir));
}