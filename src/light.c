/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:49:01 by linyao            #+#    #+#             */
/*   Updated: 2024/11/28 22:20:29 by linyao           ###   ########.fr       */
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
    ipos = vec3_sub(&lit->l_src, &ipos);
    normalize(&ipos);
    res = vec3_dot(&nor, &ipos);
    if (res < 0)
        res = -res;
    return (res);
}
