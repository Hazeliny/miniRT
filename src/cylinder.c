/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:02 by linyao            #+#    #+#             */
/*   Updated: 2024/11/28 22:08:16 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int cy_intersect(t_intersect *i, void *elm, int f)
{
    
}

void cy_update_inter(t_intersect *i, void *elm)
{
    
}

t_vec3  get_cynormal(t_cy *cy, t_vec3 pos)
{
    t_vec3  vec;
    t_vec3  proj;
    float   proj_len;

    vec = vec3_sub(&pos, cy->center);
    proj_len = vec3_dot(cy->axis, &vec);
    proj = vec3_mpl(*cy->axis, proj_len);
    vec = vec3_sub(&vec, &proj);
    normalize(&vec);
    return (vec);
}