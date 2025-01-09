/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:16:24 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 17:52:17 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

int	check_shadow(t_intersect *i, t_obj *obj, t_ray *ray)
{
	t_intersect	ins;
	t_obj		*cur;

	ins = *i;
	ins.ray = *ray;
	ins.t = ray->t_max;
	cur = obj;
	while (cur)
	{
		if (cur->vtable->is_intersect(&ins, cur, NO_UPDATE))
			return (1);
		cur = cur->next;
	}
	return (0);
}

bool	in_shadow(t_intersect *i, t_obj *obj, t_lit *lit)
{
	t_vec3	v;
	t_ray	ray;
	t_vec3	offset;

	ray.origin = i_pos(i);
	v = vec3_sub(&lit->l_src, &ray.origin);
	ray.t_max = vec3_len(v);
	ray.direction = v;
	normalize(&(ray.direction));
	offset = vec3_mpl(ray.direction, 1.1);
	ray.origin = vec3_sum(ray.origin, offset);
	if (check_shadow(i, obj, &ray))
		return (true);
	return (false);
}
