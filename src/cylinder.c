/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:02 by linyao            #+#    #+#             */
/*   Updated: 2024/12/25 19:05:28 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

//to compute the intersection of the ray with the curved surface of the cylinder
int solve_quadratic(t_intersect *i, t_vec3 lorig, t_cy *cy, float a[4])
{
    float   proj[2];

//Project ray direction and Lorig onto the cylinder's axis:
    proj[0] = vec3_dot(&i->ray.direction, &cy->axis);//ray direction’s projection onto the axis
    proj[1] = vec3_dot(&cy->axis, &lorig);//ray origin’s projection onto the axis
//Use these projections to define the quadratic coefficients:
    a[0] = vec3_sqr(i->ray.direction) - sqr(proj[0]);//Represents the squared direction perpendicular to the axis.
    a[1] = 2 * (vec3_dot(&i->ray.direction, &lorig) - proj[0] * proj[1]);//Combines the interaction between the direction and origin vectors.
    a[2] = vec3_sqr(lorig) - sqr(vec3_dot(&lorig, &cy->axis)) - \
                                                    sqr(cy->radius);//Measures the distance of 𝐿orig from the cylinder axis, subtracting the radius.
    if (get_tValue(i, a) == -1)//Solve the quadratic equation
        return (-1);
//Check the height bounds, it computes the height of the intersection along the cylinder's axis.
//If 𝑎[3] is not within [0,𝐻], the intersection lies outside the height bounds.
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
    inter = *i;//shallow copy of i
    inter.t = i->t;
    inter.ray = i->ray;//i->ray is an instance, and it isnot modified, so shallow copy is enough
    num += cy->top->vtable->is_intersect(&inter, cy->top, YES_UPDATE);
    num += cy->bottom->vtable->is_intersect(&inter, cy->bottom, YES_UPDATE);
    if (inter.t > a[0] && inter.t > a[1])
        return (0);
    i->t = inter.t;//If the ray intersects a cap closer than the side intersection, the cap intersection is used
    i->shape = inter.shape;
    return (num);
}

static int  cy_judge_inter(t_intersect *i, t_obj *obj, float t_val)
{
    t_cy    *cy;
    t_vec3  lorig;
    float   a[4];

    cy = (t_cy *)obj->elm;
    lorig = vec3_sub(&i->ray.origin, &cy->center);//Decompose 𝑃(𝑡)−𝐶: Lorig=O−C, Lorig is the vector from the cylinder's base to the ray origin.
    if (solve_quadratic(i, lorig, cy, a) == -1)//to check for curved surface intersections
        return (0);
//Validates the height bounds (𝑎[3])
    if (a[3] <= 0 || a[3] >= cy->hgt)
    {
        a[2] = vec3_dot(&i->ray.direction, &cy->axis) * a[0] + \
                vec3_dot(&lorig, &cy->axis);//represents the height of the first candidate intersection point along the cylinder's axis
        a[3] = vec3_dot(&i->ray.direction, &cy->axis) * a[1] + \
                vec3_dot(&lorig, &cy->axis);//represents the height of the second candidate intersection point along the cylinder's axis
        i->t = t_val;
        if ((a[2] < 0 && a[3] < 0) || (a[2] > cy->hgt && a[3] > cy->hgt))
            return (0);
//If valid, indicating a successful intersection with the curved surface; If invalid, it computes alternative intersection values for a[2] and a[3] to test against the caps
        return (check_cy_topbottom(i, cy, a));//Calls check_cy_topbottom() if the curved surface intersection is invalid or out of bounds
    }
    return (1);
}

int cy_intersect(t_intersect *i, t_obj *obj, int f)
{
    float   t_val;

    t_val = i->t;//Sets the t-value to the nearest valid intersection
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
//Updates the intersection position， a[3] represents the height of the first candidate intersection point along the cylinder's axis
    a[3] = vec3_dot(&i->ray.direction, &cy->axis) * a[0] + \
            vec3_dot(&lorig, &cy->axis);
    if (a[3] <= 0 || a[3] >= cy->hgt)//the intersection point lies outside the cylinder’s top or bottom boundaries. In this case, intersections with the cylinder's caps (top and bottom disks) must be considered
    {
        a[2] = vec3_dot(&i->ray.direction, &cy->axis) * a[1] + \
            vec3_dot(&lorig, &cy->axis);//represents the height of the second candidate intersection point along the cylinder's axis.
        i->t = t_val;
        if ((a[2] < 0 && a[3] < 0) || (a[2] > cy->hgt && a[3] > cy->hgt))
            return (0);
        return (check_cy_topbottom(i, cy, a));
    }
    i->shape = (t_obj *)obj;
    return (1);
}
/*
static int  cy_judge_inter(t_intersect *i, t_obj *obj, float t_val)
{
    t_cy    *cy;
    t_vec3  lorig;
    float   a[4];

    (void)t_val;
    cy = (t_cy *)obj->elm;
    lorig = vec3_sub(&i->ray.origin, &cy->center);//Decompose 𝑃(𝑡)−𝐶: Lorig=O−C, Lorig is the vector from the cylinder's base to the ray origin.
    if (solve_quadratic(i, lorig, cy, a) == -1)//to check for curved surface intersections
        return (0);
//Validates the height bounds (𝑎[3])
    if (a[3] <= 0 || a[3] >= cy->hgt)
    {
        a[2] = vec3_dot(&i->ray.direction, &cy->axis) * a[0] + \
                vec3_dot(&lorig, &cy->axis);//represents the height of the first candidate intersection point along the cylinder's axis
        a[3] = vec3_dot(&i->ray.direction, &cy->axis) * a[1] + \
                vec3_dot(&lorig, &cy->axis);//represents the height of the second candidate intersection point along the cylinder's axis
        if ((a[2] < 0 && a[3] < 0) || (a[2] > cy->hgt && a[3] > cy->hgt))
            return (check_cy_topbottom(i, cy, a));
        else
        {
            if (a[2] >= 0 && a[2] <= cy->hgt && a[0] < i->t)
                i->t = a[0];
            else if (a[3] >= 0 && a[3] <= cy->hgt && a[1] < i->t)
                i->t = a[1];
            else
                return (0);
        }
    }
    return (1);
}
*/
/*
int cy_update_inter(t_intersect *i, t_obj *obj, float t_val)
{
    t_cy    *cy;
    t_vec3  lorig;
    float   a[4];
    float   t_body;
    float   t_cap;

//    t_val = i->t;
    cy = (t_cy *)obj->elm;
    lorig = vec3_sub(&i->ray.origin, &cy->center);
    if (solve_quadratic(i, lorig, cy, a) == -1)
        return (0);
    a[2] = vec3_dot(&i->ray.direction, &cy->axis) * a[0] + \
            vec3_dot(&lorig, &cy->axis);
//Updates the intersection position， a[3] represents the height of the first candidate intersection point along the cylinder's axis
    a[3] = vec3_dot(&i->ray.direction, &cy->axis) * a[1] + \
            vec3_dot(&lorig, &cy->axis);
    t_body = FLT_MAX;
    t_cap = FLT_MAX;
    if (a[2] >= 0 && a[2] <= cy->hgt && a[0] < i->t)
        t_body = a[0];
    if (a[3] >= 0 && a[3] <= cy->hgt && a[1] < i->t)
        t_body = fmin(t_body, a[1]);
    if (check_cy_topbottom(i, cy, a))
        t_cap = i->t;
    if (t_body < t_cap && t_body < t_val)
    {
        i->t = t_body;
        i->shape = obj;
        return (1);
    }
    else if (t_cap < t_body && t_cap < t_val)
    {
        i->t = t_cap;
        i->shape = obj;
        return (1);
    }
    return (0);
}
*/