/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:17:48 by linyao            #+#    #+#             */
/*   Updated: 2024/12/17 19:37:48 by linyao           ###   ########.fr       */
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

//to compute the difference of two 3D points or vectors. The result is a vector from p2 to p1
t_vec3  vec3_sub(t_point *p1, t_point *p2)
{
    t_vec3  res;
    
    res.x = p1->x - p2->x;
    res.y = p1->y - p2->y;
    res.z = p1->z - p2->z;
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