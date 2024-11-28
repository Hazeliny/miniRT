/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:09:35 by linyao            #+#    #+#             */
/*   Updated: 2024/11/25 23:43:40 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
//combine with parser
void    init_metadata(t_rt *rt)
{
    init_al();
    init_cam();
    init_lit();
    init_obj();
}
//combine with parser
void    init_intersect(t_intersect *i)
{
    init_point();
    init_vec3();
    init_rgb();
    init_ray();
    //normalize after parsing
    normalize(&i->ray.direction);
}
//combine with parser
void    init_objs(t_obj **obj, char **str, int type)
{
    init_pl();
    init_sp();
    init_cy();
}

t_point init_point(float x, float y, float z)
{
    t_point p;

    p.x = x;
    p.y = y;
    p.z = z;
    return (p);
}

void    init_vtable(t_obj **obj)
{
    t_obj   *cur;
    t_vtable pl_vtable;
    t_vtable sp_vtable;
    t_vtable cy_vtable;

    pl_vtable.is_intersect = &pl_intersect;
    pl_vtable.update_inter = &pl_update_inter;
    sp_vtable.is_intersect = &sp_intersect;
    sp_vtable.update_inter = &sp_update_inter;
    cy_vtable.is_intersect = &cy_intersect;
    cy_vtable.update_inter = &cy_update_inter;
    cur = *obj;
    while (cur)
    {
        if (cur->typ == "pl")
            cur->vtable = &pl_vtable;
        else if (cur->typ == "sp")
            cur->vtable = &sp_vtable;
        else if (cur->typ == "cy")
            cur->vtable = &cy_vtable;
        else
        {
            // Future support for other object types (e.g., cones)
        }
        cur = cur->next;
    }
}
