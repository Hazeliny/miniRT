/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:31:02 by linyao            #+#    #+#             */
/*   Updated: 2024/12/22 17:05:27 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

//Computes the intersection point in world coordinates
t_vec3  i_pos(t_intersect *i)
{
    t_vec3  res;

    res = vec3_sum(i->ray.origin, vec3_mpl(i->ray.direction, i->t));
    return (res);
}

//calculates the surface normal vector at the intersection point of the ray with an object
t_vec3  get_normal_inter(t_intersect *i)
{
    t_pl    *pl;
    t_sp    *sp;
    t_cy    *cy;
    t_vec3  tmp;

//Each type requires a different method to calculate the normal vector
    if (i->shape->typ[0] == 'p' && i->shape->typ[1] == 'l')
    {
        pl = (t_pl *)(i->shape->elm);//A plane's normal vector is constant across its entire surface and is stored in the normal field of the t_pl structure
        return (pl->normal);
    }
    else if (i->shape->typ[0] == 's' && i->shape->typ[1] == 'p')//For a sphere, the normal at any point on its surface is a vector pointing from the sphere's center to the intersection point
    {
        sp = (t_sp *)(i->shape->elm);
        tmp = i_pos(i);//Compute the intersection position in world space
        tmp = vec3_sub(&sp->center, &tmp);//Subtract the sphere's center from the intersection position to get the raw normal vector.
        normalize(&tmp);//Normalize the resulting vector to ensure it has a unit length
        return (tmp);
    }
    else//For a cylinder, the normal depends on the intersection position relative to the curved surface or the caps
    {
        cy = (t_cy *)(i->shape->elm);
        return (get_cynormal(cy, i_pos(i)));//Curved Surface: The normal is perpendicular to the cylinder's axis and points outward; Caps: The normal is parallel to the cylinder's axis, either pointing up or down based on the cap's orientation.
    }
}

//to iterates through a linked list of objects (t_obj) in the scene and checks whether 
//the ray (stored in t_intersect *i) intersects any of these objects
//If an intersection is found:
//The is_intersect function from the corresponding object's virtual table (vtable) is invoked.
//The function returns true if any intersection is detected.
bool    obj_intersect(t_intersect *i, t_obj **obj)
{
    t_obj   *cur;
    bool    f;
    
    cur = *obj; //Pointer to the linked list of objects
    f = false;
    while (cur)
    {
        if (!ft_strcmp(cur->typ, "pl") || !ft_strcmp(cur->typ, "sp") \
                || !ft_strcmp(cur->typ, "cy"))
            if (cur->vtable->is_intersect(i, cur, YES_UPDATE))
                f = true;
        cur = cur->next;
    }
    return (f);
}