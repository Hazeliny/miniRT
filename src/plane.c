/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:00:21 by linyao            #+#    #+#             */
/*   Updated: 2024/12/17 22:00:16 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int pl_intersect(t_intersect *i, t_obj *obj, int f)
{
    t_pl    *pl;
    float   dot_dir_nor;
    float   proj_dist;
    float   t_val;
    t_vec3  tmp;
    
    pl = (t_pl *)obj->elm;
    dot_dir_nor = vec3_dot(&i->ray.direction, &pl->normal); //If dot product == 0, the ray is parallel to the plane. If dot product > 0, the ray is pointing away from the plane.
//Projection Distance
//Compute the vector tmp from the ray's origin to a point p on the plane.
//Project this vector onto the plane's normal to get the signed distance (proj_dist) from the ray origin to the plane.
    tmp = vec3_sub(&i->ray.origin, &pl->p);
    proj_dist = vec3_dot(&tmp, &pl->normal);
//Reject cases where:
//The ray is parallel to the plane (dot_dir_nor == 0).
//The ray points away from the plane (dot_dir_nor > 0) and starts behind the plane (proj_dist > 0).
    if (!dot_dir_nor || (dot_dir_nor > 0 && proj_dist > 0))
        return (0);
    t_val = -proj_dist / dot_dir_nor; //Compute the intersection point's distance along the ray, t_val. This uses the parametric ray equation Origin+𝑡⋅Direction.
    if (t_val <= T_VALUE_MIN || t_val >= i->t) //Reject Out-of-Bounds Intersections. Too close (t_val <= T_VALUE_MIN). Behind an already-closer intersection (t_val >= i->t).
        return (0);
    if (f == YES_UPDATE)
        pl_update_inter(i, obj, t_val);
    return (1);
}

int pl_update_inter(t_intersect *i, t_obj *obj, float t_val)
{
    i->t = t_val;//Update the closest intersection distance (t) to the current t_val
    i->shape = (t_obj *)obj; //Record the intersected shape (the plane object)
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