/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:16:24 by linyao            #+#    #+#             */
/*   Updated: 2024/12/25 18:58:22 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

//Tests shadow intersection for specific object types (planes, spheres, cylinders)
int check_shadow(t_intersect *i, t_obj *obj, t_ray *ray)
{
    t_intersect ins;
    t_obj   *cur;

    ins = *i;
    ins.ray = *ray;
    ins.t = ray->t_max;
    cur = obj;
    while (cur)
    {
        if (cur->vtable->is_intersect(&ins, cur, NO_UPDATE))
            return (1);
        cur = cur->next;
    }
    return (0);
//    return (obj->vtable->is_intersect(&ins, obj, NO_UPDATE));
/* the following is another alternative
    if (obj->typ[0] == 'p' && obj->typ[1] == 'l')
        return (pl_intersect(&ins, obj->elm, NO_UPDATE));
    else if (obj->typ[0] == 's' && obj->typ[1] == 'p')
        return (sp_intersect(&ins, obj->elm, NO_UPDATE));
    else
        return (cy_intersect(&ins, obj->elm, NO_UPDATE));
*/
}

//Checks whether a point is in shadow by casting a ray toward the light source and testing for intersections
bool    in_shadow(t_intersect *i, t_obj *obj, t_lit *lit)
{
    t_vec3  v;
    t_ray   ray;
    t_vec3  offset;

    ray.origin = i_pos(i);
    v = vec3_sub(&lit->l_src, &ray.origin);
    ray.t_max = vec3_len(v);
    ray.direction = v;
    normalize(&(ray.direction));
    offset = vec3_mpl(ray.direction, 1.1);
    ray.origin = vec3_sum(ray.origin, offset);//Computes the vector from the intersection to the light source
    if (check_shadow(i, obj, &ray))//Tests whether any object blocks the light source
        return (true);
    return (false);
}