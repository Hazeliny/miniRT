/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:00:21 by linyao            #+#    #+#             */
/*   Updated: 2024/12/01 21:49:14 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int pl_intersect(t_intersect *i, void *elm, int f)
{
    t_pl    *pl;
    float   dot_dir_nor;
    float   proj_dist;
    float   t_val;
    t_vec3  tmp;
    
    pl = (t_pl *)elm;
    dot_dir_nor = vec3_dot(&i->ray.direction, &pl->normal);
    tmp = vec3_sub(&pl->p, &i->ray.origin);
    proj_dist = vec3_dot(&tmp, &pl->normal);
    if (!dot_dir_nor || (dot_dir_nor > 0 && proj_dist > 0))
        return (0);
    t_val = -proj_dist / dot_dir_nor;
    if (t_val <= T_VALUE_MIN || t_val >= i->t)
        return (0);
    if (f == YES_UPDATE)
        pl_update_inter(i, elm, t_val);
    return (1);
}

int pl_update_inter(t_intersect *i, void *elm, float t_val)
{
    i->t = t_val;
    i->shape = (t_obj *)elm;
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