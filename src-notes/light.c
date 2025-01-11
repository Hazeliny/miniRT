/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:49:01 by linyao            #+#    #+#             */
/*   Updated: 2024/12/17 21:45:52 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

float   light_dot(t_intersect *i, t_lit *lit)
{
    t_vec3  ipos;
    t_vec3  nor;
    float   res;

    ipos = i_pos(i);
    nor = get_normal_inter(i);
    ipos = vec3_sub(&ipos, &lit->l_src);
    normalize(&ipos);
    res = vec3_dot(&nor, &ipos);
    if (res < 0)
        res = -res;
    return (res);
}

//to calculate specular highlights using the Phong model
t_rgb   specular(t_intersect *i, t_lit *lit)
{
    t_rgb   rgb;
    t_vec3  ipos;
    t_vec3  normal;
    float   dot;

    rgb = (t_rgb){200, 200, 200};
    ipos = i_pos(i);
    normal = get_normal_inter(i);//Computes the intersection position and normal vector
    ipos = vec3_sub(&ipos, &(lit->l_src));
    ipos = vec3_sum(ipos, i->ray.direction);
    normalize(&ipos);//Determines the light reflection vector
    dot = vec3_dot(&normal, &ipos);//Computes the dot product for specular intensity
    if (dot < 0)
        return (density(&rgb, 0));
    return (density(&rgb, pow(dot, 100)));
}

void    update_ray_color(t_rgb (*rgb)[2], t_rt *rt, t_point *p, t_rgb *ds)
{
    if (!p->y && !p->z)
    {
        (*rgb)[1] = mpl_color(rt->al.color, *ds);
        p->y = 1;
    }
}

//to apply diffuse and specular lighting based on the light source and shadows
t_rgb   light_color(t_rgb (*rgb)[2], t_rt *rt, t_intersect *i, t_point *p)
{
    t_rgb   ds;
    t_lit   *lit;

    lit = rt->lit;
    while (lit)
    {
        p->x = light_dot(i, lit);//to compute dot product of the light direction and surface normal
        ds = density(&lit->color, lit->r_brt * p->x);//to scale light color by brightness 
        if (p->x <= 0)
            return ((*rgb)[0]);
        if (in_shadow(i, rt->obj, lit))//to handle shadow checking and updates colors accordingly
            update_ray_color(rgb, rt, p, &ds);//to handle shadow cases by scaling the ambient light color with the shadowed light color
        else
        {
            p->z = 1;
            (*rgb)[1] = sum_color(sum_color(mpl_color(ds, (*rgb)[0]), \
                                specular(i, lit)), (*rgb)[1]);
        }
        lit = lit->next;
    }
    return ((*rgb)[1]);
}