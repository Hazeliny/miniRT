/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:29:12 by linyao            #+#    #+#             */
/*   Updated: 2024/12/17 18:46:53 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

//This is a scalar value indicating the extent to which the two vectors align
//to calculate dot products for angle and projection calculations
float   vec3_dot(t_vec3 *v1, t_vec3 *v2)
{
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

//to calculate a vector perpendicular to both v1 and v2
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

// to map each pixel to a point on the camera's view plane in world space
// to return a unit vector in the Z-axis plane-aligned direction
// it's used in 3D rendering pipelines to map 2D screen coordinates into 3D space, often as part of ray generation or viewport transformations
// the function ensures that the resulting vector lies on the XY plane, 
// which is useful for aligning 2D input (e.g., mouse clicks or screen positions) with 3D world calculations
t_vec3  planarize(float x, float y)
{
    t_vec3  res;

    res.x = x;
    res.y = y;
    res.z = 0;
    return (res);
}
/*
The planarize function is a simple utility to embed 2D coordinates into 
a 3D space by setting z = 0. Its usage here normalizes screen coordinates 
into the range [-1, 1] and maps them onto the XY plane for further processing 
in a 3D graphics context
*/
float   sqr(float n)
{
    return (n * n);
}