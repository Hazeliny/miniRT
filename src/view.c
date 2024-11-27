/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:31:30 by linyao            #+#    #+#             */
/*   Updated: 2024/11/27 22:40:15 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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

t_ray   create_ray(t_view *view, t_vec3 vec)
{
    
}