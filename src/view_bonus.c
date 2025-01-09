/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:31:30 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 17:25:39 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_view	create_view(t_cam *cam)
{
	t_view	view;

	view.source = cam->pov;
	normalize(&cam->n_vec);
	view.forward = cam->n_vec;
	view.right = vec3_cross(view.forward, planarize(0, 1));
	view.up = vec3_cross(view.forward, view.right);
	view.h = tan(cam->fov * M_PI / 180);
	view.w = view.h * ((float) WINX / (float) WINY);
	return (view);
}

t_ray	create_ray(t_view *view, t_vec3 vec)
{
	t_ray	ray;
	t_vec3	a;
	t_vec3	b;

	a = vec3_mpl(view->right, vec.x * view->w);
	a = vec3_sum(view->forward, a);
	b = vec3_mpl(view->up, vec.y * view->h);
	a = vec3_sum(a, b);
	ray.origin = view->source;
	normalize(&a);
	ray.direction = a;
	ray.t_max = T_VALUE_MAX;
	return (ray);
}
