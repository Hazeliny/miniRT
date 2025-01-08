/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:31:30 by linyao            #+#    #+#             */
/*   Updated: 2025/01/07 21:13:01 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

//The view is defined by the camera's position, direction, and field of view (FOV)
t_view  create_view(t_cam *cam)
{
    t_view  view;

    view.source = cam->pov;
    normalize(&cam->n_vec);
    view.forward = cam->n_vec;
    view.right = vec3_cross(view.forward, planarize(0, 1));
    view.up = vec3_cross(view.forward, view.right);
    view.h = tan(cam->fov * M_PI / 180);
    view.w = view.h * ((float) WINX / (float) WINY);
    return (view);
}

//to define a system for generating a 3D ray from a camera's view
//to use this point to compute a ray originating at the camera's position and pointing through the view plane
t_ray   create_ray(t_view *view, t_vec3 vec)
{
    t_ray   ray;
    t_vec3  a;
    t_vec3  b;

    a = vec3_mpl(view->right, vec.x * view->w); //Horizontal (view->right): Scaled by vec.x * view->w (contribution proportional to the normalized x-coordinate and view width).
    a = vec3_sum(view->forward, a); //Forward (view->forward): Always added as the ray moves "into" the scene.
    b = vec3_mpl(view->up, vec.y * view->h); //Vertical (view->up): Scaled by vec.y * view->h (contribution proportional to the normalized y-coordinate and view height).
    a = vec3_sum(a, b); //Resulting final direction is direction = view->forward + (vec.x * view->w * view->right) + (vec.y * view->h * view->up)
    ray.origin = view->source; //The ray originates from the camera's position (view->source)
    normalize(&a); //to ensure the ray's direction vector has unit length for consistent calculations in later stages.
    ray.direction = a;
    ray.t_max = T_VALUE_MAX;
    return (ray);
}
