/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:09:35 by linyao            #+#    #+#             */
/*   Updated: 2024/11/30 00:10:11 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"


void    init_obj(t_obj **obj, char **str, const char *type)
{
    t_obj   *node;
    
    node = ft_calloc(1, sizeof(t_obj));
    if (!node)
        terminate(ERR_MEMO);
    node->typ = type;
    node->next = NULL;
    if (!ft_strcmp(type, "sp"))
        node->elm = init_sp(str);
    else if (!ft_strcmp(type, "pl"))
        node->elm = init_pl(str);
    else if (!ft_strcmp(type, "cy"))
        node->elm = init_cy(str);
    if (*obj)
        (find_lstlast(obj))->next = node;
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
