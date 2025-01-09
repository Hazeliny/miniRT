/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump1_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:50:40 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 18:37:40 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	calculate_uv_sp(t_obj *obj, t_vec3 p, float *uv)
{
	t_vec3	vec;
	float	a[3];
	t_sp	*sp;

	sp = (t_sp *)obj->elm;
	vec = vec3_sub(&p, &sp->center);
	normalize(&vec);
	a[0] = vec3_dot(&obj->lx, &vec);
	a[1] = vec3_dot(&obj->ly, &vec);
	a[2] = vec3_dot(&obj->lz, &vec);
	uv[0] = atan2(a[0], a[2]) / (2 * M_PI) + 0.5;
	uv[1] = a[1] * 0.5 + 0.5;
}

t_vec3	pertub_bump_nor(t_obj *obj, t_vec3 nor, float au, float av)
{
	t_vec3	vec;
	t_vec3	pu;
	t_vec3	pv;

	vec = nor;
	pu = vec3_cross(nor, obj->ly);
	pv = vec3_cross(nor, pu);
	vec = vec3_sum(vec, vec3_mpl(pu, av));
	vec = vec3_sum(vec, vec3_mpl(pv, au));
	normalize(&vec);
	return (vec);
}
