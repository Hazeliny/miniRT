/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:56:38 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 18:48:25 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

static void	checkerboard_on_pl(t_pl *pl, t_intersect *i, t_rgb (*rgb)[2])
{
	t_vec3	relative_pos;
	float	u;
	float	v;

	relative_pos = vec3_sub(&i->pos, &pl->p);
	u = vec3_dot(&relative_pos, &pl->u_dir) * pl->tile_scale;
	v = vec3_dot(&relative_pos, &pl->v_dir) * pl->tile_scale;
	if (((int)floor(u) + (int)floor(v)) % 2 == 0)
		(*rgb)[0] = pl->rgb;
	else
		(*rgb)[0] = (t_rgb){0, 0, 0};
}

void	apply_checkerboard(t_intersect *i, t_rgb (*rgb)[2])
{
	if (!i->shape->has_checkerboard)
		return ;
	if (!ft_strcmp(i->shape->typ, "pl"))
		checkerboard_on_pl((t_pl *)i->shape->elm, i, rgb);
}
