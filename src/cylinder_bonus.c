/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:02 by linyao            #+#    #+#             */
/*   Updated: 2025/01/06 16:40:20 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

int solve_quadratic(t_intersect *i, t_vec3 lorig, t_cy *cy, float a[4])
{
    float   proj[2];

    proj[0] = vec3_dot(&i->ray.direction, &cy->axis);
    proj[1] = vec3_dot(&cy->axis, &lorig);
    a[0] = vec3_sqr(i->ray.direction) - sqr(proj[0]);
    a[1] = 2 * (vec3_dot(&i->ray.direction, &lorig) - proj[0] * proj[1]);
    a[2] = vec3_sqr(lorig) - sqr(vec3_dot(&lorig, &cy->axis)) - \
                                                    sqr(cy->radius);
    if (get_tValue(i, a) == -1)
        return (-1);
    a[3] = vec3_dot(&i->ray.direction, &cy->axis) * i->t + \
                                            vec3_dot(&lorig, &cy->axis);
    return (0);
}

//to check whether the ray intersects the top or bottom caps of the cylinder
//The top and bottom caps are treated as disks: 
//For the top cap, translate 𝐶 by 𝐻 along the axis; 
//Compute the intersection using the disk’s plane equation
int check_cy_topbottom(t_intersect *i, t_cy *cy, float *a)
{
    t_intersect inter;
    int         num;

    num = 0;
    inter = *i;
    inter.t = i->t;
    inter.ray = i->ray;
    num += cy->top->vtable->is_intersect(&inter, cy->top, YES_UPDATE);
    num += cy->bottom->vtable->is_intersect(&inter, cy->bottom, YES_UPDATE);
    if (inter.t > a[0] && inter.t > a[1])
        return (0);
    i->t = inter.t;
    i->shape = inter.shape;
    return (num);
}

static int  cy_judge_inter(t_intersect *i, t_obj *obj, float t_val)
{
    t_cy    *cy;
    t_vec3  lorig;
    float   a[4];

    cy = (t_cy *)obj->elm;
    lorig = vec3_sub(&i->ray.origin, &cy->center);
    if (solve_quadratic(i, lorig, cy, a) == -1)
        return (0);
    if (a[3] <= 0 || a[3] >= cy->hgt)
    {
        a[2] = vec3_dot(&i->ray.direction, &cy->axis) * a[0] + \
                vec3_dot(&lorig, &cy->axis);
        a[3] = vec3_dot(&i->ray.direction, &cy->axis) * a[1] + \
                vec3_dot(&lorig, &cy->axis);
        i->t = t_val;
        if ((a[2] < 0 && a[3] < 0) || (a[2] > cy->hgt && a[3] > cy->hgt))
            return (0);
        return (check_cy_topbottom(i, cy, a));
    }
    return (1);
}

int cy_intersect(t_intersect *i, t_obj *obj, int f)
{
    float   t_val;

    t_val = i->t;
    if (f == NO_UPDATE)
    {
        if (cy_judge_inter(i, obj, t_val) != 0)
            return (1);
    }
    else
    {
        if (cy_update_inter(i, obj, t_val) != 0)
            return (1);
    }
    return (0);
}

int cy_update_inter(t_intersect *i, t_obj *obj, float t_val)
{
    t_cy    *cy;
    t_vec3  lorig;
    float   a[4];

//    t_val = i->t;
    cy = (t_cy *)obj->elm;
    lorig = vec3_sub(&i->ray.origin, &cy->center);
    if (solve_quadratic(i, lorig, cy, a) == -1)
        return (0);
    a[3] = vec3_dot(&i->ray.direction, &cy->axis) * a[0] + \
            vec3_dot(&lorig, &cy->axis);
    if (a[3] <= 0 || a[3] >= cy->hgt)
    {
        a[2] = vec3_dot(&i->ray.direction, &cy->axis) * a[1] + \
            vec3_dot(&lorig, &cy->axis);
        i->t = t_val;
        if ((a[2] < 0 && a[3] < 0) || (a[2] > cy->hgt && a[3] > cy->hgt))
            return (0);
        return (check_cy_topbottom(i, cy, a));
    }
    i->shape = (t_obj *)obj;
    i->pos = vec3_sum(i->ray.origin, vec3_mpl(i->ray.direction, i->t));
    i->nor = get_cynormal((t_cy *)(i->shape->elm), i_pos(i));
    normalize(&i->nor);
    return (1);
}