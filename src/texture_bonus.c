/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:40:15 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 18:59:30 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_vec3	calculate_tangent(t_vec3 normal)
{
	t_vec3	tangent;
	t_vec3	ref;

	if (fabs(normal.x) > 0.9)
		ref = (t_vec3){0, 1, 0};
	else
		ref = (t_vec3){1, 0, 0};
	tangent = vec3_cross(normal, ref);
	normalize(&tangent);
	return (tangent);
}

t_vec3	perturb_texture_nor(t_vec3 normal, t_vec3 texture_nor)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	perturbed_normal;

	tangent = calculate_tangent(normal);
	bitangent = vec3_cross(normal, tangent);
	perturbed_normal = vec3_sum(vec3_mpl(tangent, texture_nor.x), \
			vec3_sum(vec3_mpl(bitangent, texture_nor.y), \
			vec3_mpl(normal, texture_nor.z)));
	normalize(&perturbed_normal);
	return (perturbed_normal);
}

t_rgb	texture_on_sp(t_intersect *i, t_bitmap *bm)
{
	float	uv[2];
	t_vec3	texture_nor;
	t_rgb	texture_rgb;

	calculate_uv_sp(i->shape, i_pos(i), uv);
	texture_nor = get_normal_from_texture(bm, uv);
	i->nor = perturb_texture_nor(i->nor, texture_nor);
	texture_rgb = get_pixelcolor(bm, uv[0], uv[1]);
	return (texture_rgb);
}

t_rgb	mix_colors(t_rgb base_color, t_rgb texture_color, float mix_factor)
{
	t_rgb	res_color;

	res_color.r = (1 - mix_factor) * base_color.r + mix_factor * \
					(base_color.r * texture_color.r / 255);
	res_color.g = (1 - mix_factor) * base_color.g + mix_factor * \
					(base_color.g * texture_color.g / 255);
	res_color.b = (1 - mix_factor) * base_color.b + mix_factor * \
					(base_color.b * texture_color.b / 255);
	if (res_color.r > 255)
		res_color.r = 255;
	if (res_color.g > 255)
		res_color.g = 255;
	if (res_color.b > 255)
		res_color.b = 255;
	return (res_color);
}

void	apply_texture(t_intersect *i, t_rgb (*rgb)[2])
{
	t_rgb	texture_color;

	if (!i->shape->has_texture)
		return ;
	if (!ft_strcmp(i->shape->typ, "sp"))
	{
		texture_color = texture_on_sp(i, &i->shape->texture);
		(*rgb)[0] = mix_colors((*rgb)[0], texture_color, 0.6);
	}
}
