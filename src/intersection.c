/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:31:02 by linyao            #+#    #+#             */
/*   Updated: 2024/11/28 00:04:33 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vec3  i_pos(t_intersect *i)
{
    t_vec3  res;

    res = vec3_sum(i->ray.origin, vec3_mpl(i->ray.direction, i->t));
    return (res);
}

t_vec3  get_normal_inter(t_intersect *i)
{
    t_pl    *pl;
    t_sp    *sp;
    t_cy    *cy;

    if (i->shape->typ[0] == 'p' && i->shape->typ[1] == 'l')
    {
        pl = (t_pl *)(i->shape);
        return (pl->normal);
    }
}

bool    obj_intersect(t_intersect *i, t_obj **obj)
{
    t_obj   *cur;
    bool    f;
    
    cur = *obj;
    f = false;
    while (cur)
    {
        if (cur->vtable->is_intersect(i, cur, YES_UPDATE))
            f = true;
        cur = cur->next;
    }
    return (f);
}