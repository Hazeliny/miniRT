/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:16:24 by linyao            #+#    #+#             */
/*   Updated: 2024/12/01 21:48:04 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int check_shadow(t_intersect *i, t_obj *obj, t_ray *ray)
{
    int res;
    t_intersect ins;
    
    ins.ray = *ray;
    ins.t = ray->t_max;
    if (obj->typ[0] == 'p' && obj->typ[1] == 'l')
        return (pl_intersect(i, obj->elm, NO_UPDATE));
    else if (obj->typ[0] == 's' && obj->typ[1] == 'p')
        return (sp_intersect(i, obj->elm, NO_UPDATE));
    else
        return (cy_intersect(i, obj->elm, NO_UPDATE));
}

bool    in_shadow(t_intersect *i, t_obj *obj, t_lit *lit)
{
    t_vec3  v;
    t_ray   ray;
    t_vec3  offset;

    ray.origin = i_pos(i);
    v = vec3_sub(&ray.origin, &lit->l_src);
    ray.t_max = vec3_len(v);
    normalize(&(ray.direction));
    offset = vec3_mpl(ray.direction, 1.1);
    ray.origin = vec3_sum(ray.origin, offset);
    if (check_shadow(i, obj, &ray))
        return (true);
    return (false);
}