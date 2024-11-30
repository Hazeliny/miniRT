/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:00:21 by linyao            #+#    #+#             */
/*   Updated: 2024/11/30 15:12:37 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int pl_intersect(t_intersect *i, void *elm, int f)
{
    
}

void pl_update_inter(t_intersect *i, void *elm)
{
    
}

t_vec3  get_plnormal(t_vec3 vec)
{
    t_vec3  nor;

    normalize(&vec);
    nor = vec3_cross(vec, vec3_cross(planarize(0, 1), vec));
    if (!nor.x && !nor.y && !nor.z)
        nor.x = 1;
    normalize(&nor);
    return (nor);
}