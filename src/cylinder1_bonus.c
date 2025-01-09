/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:03:01 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 18:15:14 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_obj	*init_surface(t_cy *cy, int surface)
{
	t_obj	*new;
	t_pl	*pl;

	pl = ft_calloc_new(1, sizeof(t_pl));
	pl->p = cy->center;
	if (surface)
		pl->normal = vec3_mpl(cy->axis, -1);
	else
	{
		pl->p = vec3_sum(vec3_mpl(cy->axis, cy->hgt), cy->center);
		pl->normal = cy->axis;
	}
	pl->rgb = cy->rgb;
	new = ft_calloc_new(1, sizeof(t_obj));
	new->elm = pl;
	ft_strlcpy(new->typ, "pl", 3);
	init_vtable(new);
	return (new);
}

t_vec3	get_cynormal(t_cy *cy, t_vec3 pos)
{
	t_vec3	vec;
	t_vec3	proj;
	float	proj_len;

	vec = vec3_sub(&cy->center, &pos);
	proj_len = vec3_dot(&cy->axis, &vec);
	proj = vec3_mpl(cy->axis, proj_len);
	vec = vec3_sub(&proj, &vec);
	normalize(&vec);
	return (vec);
}
