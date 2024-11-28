/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:49:01 by linyao            #+#    #+#             */
/*   Updated: 2024/11/28 16:49:04 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

float   light_dot(t_intersect *i, t_lit *lit)
{
    t_vec3  ipos;
    t_vec3  nor;

    ipos = i_pos(i);
    nor = get_normal_inter(i);
    
}
