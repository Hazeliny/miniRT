/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:29:12 by linyao            #+#    #+#             */
/*   Updated: 2025/01/05 13:23:38 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

float   vec3_dot(t_vec3 *v1, t_vec3 *v2)
{
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec3  vec3_cross(t_vec3 v1, t_vec3 v2)
{
    t_vec3  res;

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    return (res);
}

void    normalize(t_vec3 *nor)
{
    float   len;
    
    len = sqrt(sqr(nor->x) + sqr(nor->y) + sqr(nor->z));
    if (len > EPSILON)
    {
        nor->x /= len;
        nor->y /= len;
        nor->z /= len;
    }
}

t_vec3  planarize(float x, float y)
{
    t_vec3  res;

    res.x = x;
    res.y = y;
    res.z = 0;
    return (res);
}

float   sqr(float n)
{
    return (n * n);
}