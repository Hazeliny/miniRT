/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:55:03 by linyao            #+#    #+#             */
/*   Updated: 2024/12/17 19:51:34 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

//to calculate the intersection points (𝑡) of a ray with a sphere by solving a quadratic equation
int get_tValue(t_intersect *i, float *a)
{
    float   discriminant;
    float   t[2];

    discriminant = sqr(a[1]) - 4.0f * a[0] * a[2];
//The discriminant determines the nature of the roots:
//discriminant<0: No intersection (ray misses the sphere); 
//discriminant=0: Tangent (ray grazes the sphere).
//discriminant>0: Two points of intersection (ray passes through the sphere).
    if (discriminant < 0)
        return (-1);
//Solve the quadratic equation for the two roots. t[0]: Closer intersection point. t[1]: Farther intersection point.
    t[0] = (-a[1] - sqrt(discriminant)) / (2.0f * a[0]);
    t[1] = (-a[1] + sqrt(discriminant)) / (2.0f * a[0]);
//Greater than a minimum threshold, less than the current closest 𝑡 in i->t, update i->t with the closest valid 𝑡
    if (t[0] > T_VALUE_MIN && t[0] < i->t && t[0] < t[1])
        i->t = t[0];
    else if (t[1] > T_VALUE_MIN && t[1] < i->t)
        i->t = t[1];
    else
        return (-1);
//to store the roots for potential further processing
    a[0] = t[0];
    a[1] = t[1];
    return (0);
}

int sp_intersect(t_intersect *i, t_obj *obj, int f)
{
    t_sp    *sp;
    t_ray   ray;
    t_vec3  oc; //vector O-C
    float   a[3];
    float   t_val;

    sp = (t_sp *)obj->elm;
    ray = i->ray;
//Vector from Ray Origin to Sphere Center.
    oc = vec3_sub(&ray.origin, &sp->center);
//Quadratic Coefficients
    a[0] = vec3_dot(&ray.direction, &ray.direction);//a[0]: Dot product of ray direction with itself (always positive). a[0]: Measures how the direction vector 𝐷 contributes to the equation. If 𝐷 is normalized, 𝑎[0]=1.
    a[1] = 2.0f * vec3_dot(&oc, &ray.direction);//a[1]: Projection of 𝑂𝐶 onto the ray direction. a[1]: Determines the linear relationship between the ray's direction and the sphere. Specifically, it measures how much OC aligns with 𝐷
    a[2] = vec3_dot(&oc, &oc) - sqr(sp->radius);//a[2]: Squared distance from ray origin to sphere minus squared radius. Represents the initial distance of the ray origin from the sphere's surface. It considers the squared distance from the ray origin to the sphere center and subtracts the squared radius
    if (get_tValue(i, a) == -1)
        return (0);
    t_val = 0.0f;
    if (f == YES_UPDATE)
        sp_update_inter(i, obj, t_val);
    return (1);
}

int sp_update_inter(t_intersect *i, t_obj *obj, float t_val)
{
//    t_sp    *sp;

    (void)t_val;
//    sp = (t_sp *)obj->elm;
    i->shape = (t_obj *)obj;
/*
//to compute the intersection point using the ray equation
    i->pos.x = i->ray.origin.x + i->t * i->ray.direction.x;
    i->pos.y = i->ray.origin.y + i->t * i->ray.direction.y;
    i->pos.z = i->ray.origin.z + i->t * i->ray.direction.z;
//to compute the surface normal at the intersection point: Normal=Intersection Point−Sphere Center. Normalize the vector to ensure its magnitude is 1
    i->nor = vec3_sub(&i->pos, &sp->center);
    normalize(&i->nor);
*/
    return (1);
}