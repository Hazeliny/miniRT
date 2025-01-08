/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:03:01 by linyao            #+#    #+#             */
/*   Updated: 2024/12/26 21:09:53 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_obj   *init_surface(t_cy *cy, int surface)
{
    t_obj   *new;
    t_pl    *pl;

    pl = ft_calloc_new(1, sizeof(t_pl));
    pl->p = cy->center;
    if (surface)
        pl->normal = vec3_mpl(cy->axis, -1);
    else
    {
        pl->p = vec3_sum(vec3_mpl(cy->axis, cy->hgt), cy->center);
        pl->normal = cy->axis;
    }
    pl->rgb = cy->rgb;
    new = ft_calloc_new(1, sizeof(t_obj));
    new->elm = pl;
    ft_strlcpy(new->typ, "pl", 3);
    init_vtable(new);
//    new->vtable->is_intersect = &pl_intersect;
//    new->vtable->update_inter = &pl_update_inter;
    return (new);
}

//calculates the surface normal vector at a given position on the curved surface of a cylinder
t_vec3  get_cynormal(t_cy *cy, t_vec3 pos)
{
    t_vec3  vec;
    t_vec3  proj;
    float   proj_len;

    vec = vec3_sub(&cy->center, &pos);//Compute the Vector V from the Cylinder Center to the Position. This vector V points from the base center of the cylinder to the position on the surface
    proj_len = vec3_dot(&cy->axis, &vec);//Project vec Onto the Cylinder's Axis. 
    proj = vec3_mpl(cy->axis, proj_len);//isolates the component of V that is parallel to the cylinder's axis, effectively projecting V onto the axis
    vec = vec3_sub(&proj, &vec);//Subtract the Projection to Get the Perpendicular Component. removes the parallel component, leaving only the perpendicular component, which points outward from the axis to the surface of the cylinder
    normalize(&vec);//Normalize the Resulting Vector. Ensures the resulting vector is a unit vector (length = 1), which is required for lighting and shading calculations
    return (vec);
}