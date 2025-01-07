/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:31:30 by linyao            #+#    #+#             */
/*   Updated: 2024/12/27 14:46:46 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

//The view is defined by the camera's position, direction, and field of view (FOV)
t_view  create_view(t_cam *cam)
{
    t_view  view;

    view.source = cam->pov; //Sets the source of the view to the camera's pov (Point of View). This is the position of the camera in 3D space.
    normalize(&cam->n_vec);//Normalizes the camera's n_vec ("normal vector" representing the camera's forward direction) to ensure it has a unit length. This is important for consistent calculations involving directions.
    view.forward = cam->n_vec; //Sets the forward vector of the view to the normalized camera's direction vector. This vector points in the direction the camera is facing.
    view.right = vec3_cross(view.forward, planarize(0, 1)); //to Compute the right vector of the view using a cross product, the result is a vector that points to the right of the camera, perpendicular to the forward vector
    view.up = vec3_cross(view.forward, view.right); //The up vector is perpendicular to both the forward and right vectors, ensuring a complete orthogonal basis for the camera's orientation in 3D space.
    view.h = tan(cam->fov * M_PI / 180);//to Calculate the height of the view frustum in normalized units, cam->fov is the field of view (in degrees), which is converted to radians (* M_PI / 180), The tangent of half the FOV angle determines the vertical size of the view at a unit distance
    view.w = view.h * ((float) WINX / (float) WINY);//Calculates the width of the view frustum based on the height and the aspect ratio of the viewport. This ensures the view frustum has the correct proportions to avoid distortion.
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
