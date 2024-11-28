/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:55:03 by linyao            #+#    #+#             */
/*   Updated: 2024/11/28 23:02:39 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int get_tValue(t_intersect *i, float *a)
{
    float   discriminant;
    float   t[2];

    discriminant = sqrtf(a[1]) - 4.0f * a[0] * a[2];
    if (discriminant < 0)
        return (0);
    t[0] = (-a[1] - sqrtf(discriminant)) / (2.0f * a[0]);
    t[1] = (-a[1] + sqrtf(discriminant)) / (2.0f * a[0]);
    if (t[0] > T_VALUE_MIN && t[0] < i->t && t[0] < t[1])
        i->t = t[0];
    else if (t[1] > T_VALUE_MIN && t[1] < i->t)
        i->t = t[1];
    else
        return (0);
    return (1);
}

int sp_intersect(t_intersect *i, void *elm, int f)
{
    t_sp    *sp;
    t_ray   ray;
    t_vec3  oc; //vector O-C
    float   a[3];

    sp = (t_sp *)elm;
    ray = i->ray;
    oc = vec3_sub(&ray.origin, sp->center);
    a[0] = vec3_dot(&ray.direction, &ray.direction);
    a[1] = 2.0f * vec3_dot(&oc, &ray.direction);
    a[2] = vec3_dot(&oc, &oc) - sqrtf(sp->radius);
    if (get_tValue(i, a) == 0)
        return (0);
    if (f == YES_UPDATE)
        sp_update_inter(i, elm);
    return (1);
}

void sp_update_inter(t_intersect *i, void *elm)
{
    t_sp    *sp;

    sp = (t_sp *)elm;
    i->shape = (t_obj *)elm;
    i->pos->x = i->ray.origin.x + i->t * i->ray.direction.x;
    i->pos->y = i->ray.origin.y + i->t * i->ray.direction.y;
    i->pos->z = i->ray.origin.z + i->t * i->ray.direction.z;
    i->nor = vec3_sub(i->pos, sp->center);
    normalize(&i->nor);
}