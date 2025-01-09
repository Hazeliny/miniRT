/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:23:28 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 12:51:28 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_sp	*init_sp(char **ss)
{
	t_sp	*new_sp;
	int		i;

	i = 0;
	while (ss[i])
		i++;
	new_sp = ft_calloc_new(1, sizeof(t_sp));
	if (!new_sp)
		terminate(ERR_MEMO);
	if (i != 4)
		terminate(ERR_ARGV);
	init_sp_center(ss[1], new_sp);
	init_sp_radius(ss[2], new_sp);
	init_sp_rgb(ss[3], new_sp);
	return (new_sp);
}

t_pl	*init_pl(char **ss)
{
	t_pl	*new_pl;
	int		i;

	i = 0;
	while (ss[i])
		i++;
	new_pl = ft_calloc_new(1, sizeof(t_pl));
	if (!new_pl)
		terminate(ERR_MEMO);
	if (i != 4 && i != 6)
		terminate(ERR_ARGV);
	init_pl_p(ss[1], new_pl);
	init_pl_n_vec(ss[2], new_pl);
	init_pl_rgb(ss[3], new_pl);
	new_pl->normal = get_plnormal(new_pl->n_vec);
	init_pl_uv(new_pl);
	new_pl->tile_scale = 0.1f;
	return (new_pl);
}

t_cy	*init_cy(char **ss)
{
	t_cy	*new_cy;
	int		i;

	i = 0;
	while (ss[i])
		i++;
	new_cy = ft_calloc_new(1, sizeof(t_cy));
	if (!new_cy)
		terminate(ERR_MEMO);
	if (i != 6)
		terminate(ERR_ARGV);
	init_cy_center(ss[1], new_cy);
	init_cy_axis(ss[2], new_cy);
	new_cy->radius = init_cy_float(ss[3]) / 2;
	new_cy->hgt = init_cy_float(ss[4]);
	init_cy_rgb(ss[5], new_cy);
	new_cy->top = init_surface(new_cy, TOP);
	new_cy->bottom = init_surface(new_cy, BOTTOM);
	normalize(&new_cy->axis);
	return (new_cy);
}

t_cn	*init_cn(char **ss)
{
	t_cn	*new_cn;
	int		i;

	i = 0;
	while (ss[i])
		i++;
	new_cn = ft_calloc_new(1, sizeof(t_cn));
	if (!new_cn)
		terminate("cn callocation failed\n");
	if (i != 6)
		terminate("incorrect numbers of cn parameters\n");
	init_cn_apex(ss[1], new_cn);
	init_cn_axis(ss[2], new_cn);
	new_cn->has_caps = true;
	new_cn->radius = init_cn_float(ss[3]) / 2;
	new_cn->hgt = init_cn_float(ss[4]);
	new_cn->angle = atan(new_cn->radius / new_cn->hgt);
	new_cn->center = vec3_sum(new_cn->apex, \
				vec3_mpl(new_cn->axis, new_cn->hgt));
	init_cn_rgb(ss[5], new_cn);
	new_cn->bottom = init_cn_surface(new_cn);
	normalize(&new_cn->axis);
	return (new_cn);
}
