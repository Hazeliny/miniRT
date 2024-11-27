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