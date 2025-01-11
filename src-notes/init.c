/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:09:35 by linyao            #+#    #+#             */
/*   Updated: 2024/12/17 19:47:24 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"


void    init_obj(t_obj **obj, char **str, const char *type)
{
    t_obj   *node;

    node = ft_calloc_new(1, sizeof(t_obj));
    ft_strlcpy(node->typ, type, 3);
    node->next = NULL;
    init_vtable(node);
    if (!ft_strcmp(type, "sp"))
        node->elm = init_sp(str);
    else if (!ft_strcmp(type, "pl"))
        node->elm = init_pl(str);
    else if (!ft_strcmp(type, "cy"))
        node->elm = init_cy(str);
    else
    {
        free(node);
        terminate("Unknown object type");
    }
    if (*obj)
        (find_lstlast_obj(obj))->next = node;
    else
        (*obj) = node;
}

t_point init_point(float x, float y, float z)
{
    t_point p;

    p.x = x;
    p.y = y;
    p.z = z;
    return (p);
}

t_rgb   init_rgb(int r, int g, int b)
{
    t_rgb   rgb;

    rgb.r = r;
    rgb.g = g;
    rgb.b = b;
    return (rgb);
}

void    init_vtable(t_obj *obj)
{
    t_obj   *cur;

    cur = obj;
    cur->vtable = ft_calloc_new(1, sizeof(t_vtable));
    if (!ft_strcmp(cur->typ, "pl"))
    {
        cur->vtable->is_intersect = &pl_intersect;
        cur->vtable->update_inter = &pl_update_inter;
    }
    else if (!ft_strcmp(cur->typ, "sp"))
    {
        cur->vtable->is_intersect = &sp_intersect;
        cur->vtable->update_inter = &sp_update_inter;
    }
    else if (!ft_strcmp(cur->typ, "cy"))
    {
        cur->vtable->is_intersect = &cy_intersect;
        cur->vtable->update_inter = &cy_update_inter;
    }
    else
    {
        free(cur->vtable);
        free(cur);
        terminate("Unknown object type");// Future support for other object types (e.g., cones)
    }
}
//t_vtable: Encapsulates type-specific behavior for ray-object intersections. 
//It decouples intersection logic for different object types, allowing the code to work polymorphically 
//(e.g., you don't need to write a long switch or if chain every time).
//initialization: all objects are assigned appropriate vtables based on their type
/*
t_vtable *init_vtable(t_obj **obj);
{
    t_obj   *cur;
    t_vtable *pl_vtable;
    t_vtable *sp_vtable;
    t_vtable *cy_vtable;

    pl_vtable = ft_calloc_new(1, sizeof(t_vtable));
    sp_vtable = ft_calloc_new(1, sizeof(t_vtable));
    cy_vtable = ft_calloc_new(1, sizeof(t_vtable));
    if (!pl_vtable || !sp_vtable || !cy_vtable)
        terminate(ERR_MEMO);
    pl_vtable->is_intersect = &pl_intersect;
    pl_vtable->update_inter = &pl_update_inter;
    sp_vtable->is_intersect = &sp_intersect;
    sp_vtable->update_inter = &sp_update_inter;
    cy_vtable->is_intersect = &cy_intersect;
    cy_vtable->update_inter = &cy_update_inter;
    cur = *obj;
    while (cur)
    {
        if (!ft_strcmp(cur->typ, "pl"))
            cur->vtable = pl_vtable;
        else if (!ft_strcmp(cur->typ, "sp"))
            cur->vtable = sp_vtable;
        else if (!ft_strcmp(cur->typ, "cy"))
            cur->vtable = cy_vtable;
        else
        {
            // Future support for other object types (e.g., cones)
        }
        cur = cur->next;
    }
}
*/