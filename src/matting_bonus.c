/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:55:57 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 19:34:15 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_vec3	compute_half_vector(t_intersect *i, t_view *view)
{
	t_vec3	h;

	h = vec3_sum(i->ray.direction, view->forward);
	normalize(&h);
	return (h);
}

float	ggx_distribution(t_vec3 *nor, t_vec3 *h, float roughness)
{
	float	nh;
	float	alpha;
	float	denom;

	nh = vec3_dot(nor, h);
	if (nh <= 0.0)
		return (0.0);
	alpha = sqr(roughness);
	denom = sqr(nh) * (alpha - 1.0) + 1.0;
	return (alpha / (M_PI * sqr(denom)));
}

float	compute_smith_geometry(t_intersect *i, float roughness)
{
	t_vec3	a[3];
	float	ndot[2];
	float	k;
	float	g1_v;
	float	g1_l;

	a[0] = i->nor;
	a[1] = i->ray.direction;
	a[2] = vec3_mpl(a[1], -1);
	ndot[0] = vec3_dot(&a[0], &a[2]);
	ndot[1] = vec3_dot(&a[0], &a[1]);
	k = sqr(roughness + 1.0) / 8.0;
	g1_v = ndot[0] / (ndot[0] * (1.0 - k) + k);
	g1_l = ndot[1] / (ndot[1] * (1.0 - k) + k);
	return (g1_v * g1_l);
}

float	compute_fresnel(t_intersect *i, float f0)
{
	float	cos_theta;

	cos_theta = vec3_dot(&i->ray.direction, &i->nor);
	if (cos_theta < 0.0f)
		cos_theta = 0.0f;
	return (f0 + (1.0f - f0) * powf(1.0f - cos_theta, 5.0f));
}

t_rgb	matting(t_intersect *i, t_lit *lit, t_rgb ds, t_rgb (*rgb)[2])
{
	float	rough;
	t_vec3	a[2];
	float	b[2];
	float	dgf[3];

	rough = i->shape->texture_f;
	a[0] = vec3_mpl(i->ray.direction, -1);
	a[1] = vec3_mpl(i->ray.direction, -1);
	normalize(&i->shape->h);
	dgf[0] = ggx_distribution(&i->nor, &i->shape->h, rough);
	dgf[1] = compute_smith_geometry(i, rough);
	dgf[2] = compute_fresnel(i, 0.04f);
	b[0] = vec3_dot(&i->nor, &a[1]);
	b[1] = vec3_dot(&i->nor, &a[0]);
	if (b[1] > 0.0f && b[0] > 0.0f)
	{
		(*rgb)[1] = sum_color(sum_color(mpl_color(ds, (*rgb)[0]), \
		density(&lit->color, (dgf[0] * dgf[1] * dgf[2]) / \
						(4.0f * b[0] * b[1]))), (*rgb)[1]);
	}
	return ((*rgb)[1]);
}
