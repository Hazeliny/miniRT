/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_ctrl_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:23:09 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 16:47:26 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_vec3	i_pos(t_intersect *i)
{
	t_vec3	res;

	res = vec3_sum(i->ray.origin, vec3_mpl(i->ray.direction, i->t));
	return (res);
}

t_vec3	set_coord(float x, float y, float z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
