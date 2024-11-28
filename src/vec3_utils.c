/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:17:48 by linyao            #+#    #+#             */
/*   Updated: 2024/11/28 23:46:26 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

float   vec3_sqr(t_vec3 v)
{
    return (sqr(v.x) + sqr(v.y) + sqr(v.z));
}

float   vec3_len(t_vec3 v)
{
    float   tmp;

    tmp = vec3_sqr(v);
    if (tmp == 0)
        return (1);
    return (sqrt(tmp));
}

t_vec3  vec3_sub(t_point *p1, t_point *p2)
{
    t_vec3  res;
    
    res.x = p1->x - p2->x;
    res.y = p1->y - p2->y;
    res.y = p1->z - p2->z;
    return (res);
}

t_vec3  vec3_sum(t_vec3 v1, t_vec3 v2)
{
    t_vec3  res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    return (res);
}

t_vec3  vec3_mpl(t_vec3 v1, float num)
{
    t_vec3  res;

    res.x = v1.x * num;
    res.y = v1.y * num;
    res.z = v1.z * num;
    return (res);
}

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
    
    len = sqrtf(sqr(nor->x) + sqr(nor->y) + sqr(nor->z));
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