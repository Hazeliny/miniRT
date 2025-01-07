/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:23:26 by linyao            #+#    #+#             */
/*   Updated: 2025/01/04 21:40:09 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

static int	solve_cn_quadratic(t_intersect *i, t_vec3 oc, t_cn *cn, float a[4])
{
	float	k;

	k = sqr(cn->radius / cn->hgt);
	a[0] = vec3_dot(&i->ray.direction, &i->ray.direction) - (1 + k) * \
			sqr(vec3_dot(&i->ray.direction, &cn->axis));
	a[1] = 2.0f * (vec3_dot(&i->ray.direction, &oc) - (1 + k) * \
			vec3_dot(&i->ray.direction, &cn->axis) * vec3_dot(&oc, &cn->axis));
	a[2] = vec3_dot(&oc, &oc) - (1 + k) * sqr(vec3_dot(&oc, &cn->axis));
	if (get_tValue(i, a) == -1)
		return (-1);
	a[3] = vec3_dot(&i->ray.direction, &cn->axis) * i->t \
		+ vec3_dot(&oc, &cn->axis);
	return (0);
}

int	i_cn_bottom(t_intersect *i, t_cn *cn, float *a)
{
	t_intersect	inter;
	int			num;
	t_vec3		bottom_center_to_inter;
	float		dist_sq;
	float		bottom_radius_sq;

	num = 0;
	inter = *i;
	inter.t = i->t;
	inter.ray = i->ray;
	num += cn->bottom->vtable->is_intersect(&inter, cn->bottom, YES_UPDATE);
	bottom_center_to_inter = vec3_sub(&inter.pos, &cn->center);
	dist_sq = vec3_dot(&bottom_center_to_inter, &bottom_center_to_inter);
	bottom_radius_sq = sqr(cn->radius);
	if (dist_sq > bottom_radius_sq)
		return (0);
	if (inter.t > a[0] && inter.t > a[1])
		return (0);
	if (num > 0 && inter.t < i->t)
	{
		i->t = inter.t;
		i->shape = inter.shape;
	}
	return (num);
}

int	cn_judge_inter(t_intersect *i, t_obj *obj, float t_val)
{
	t_cn	*cn;
	t_vec3	oc;
	float	a[4];

	cn = (t_cn *)obj->elm;
	oc = vec3_sub(&i->ray.origin, &cn->apex);
	if (solve_cn_quadratic(i, oc, cn, a) == -1)
		return (0);
	if (a[3] <= 0 || a[3] >= cn->hgt)
	{
		a[2] = vec3_dot(&i->ray.direction, &cn->axis) * a[0] + \
				vec3_dot(&oc, &cn->axis);
		a[3] = vec3_dot(&i->ray.direction, &cn->axis) * a[1] + \
				vec3_dot(&oc, &cn->axis);
		i->t = t_val;
		if ((a[2] < 0 && a[3] < 0) || (a[2] > cn->hgt && a[3] > cn->hgt))
			return (0);
		return (cn->has_caps && i_cn_bottom(i, cn, a));
	}
	return (1);
}

int	cn_update_inter(t_intersect *i, t_obj *obj, float t_val)
{
	t_cn	*cn;
	t_vec3	oc;
	float	a[4];

	cn = (t_cn *)obj->elm;
	oc = vec3_sub(&i->ray.origin, &cn->apex);
	if (solve_cn_quadratic(i, oc, cn, a) == -1)
		return (0);
	a[3] = vec3_dot(&i->ray.direction, &cn->axis) * a[0] \
					+ vec3_dot(&oc, &cn->axis);
	if (a[3] <= 0 || a[3] >= cn->hgt)
	{
		a[2] = vec3_dot(&i->ray.direction, &cn->axis) * a[1] + \
				vec3_dot(&oc, &cn->axis);
		i->t = t_val;
		if ((a[2] < 0 && a[3] < 0) || (a[2] > cn->hgt && a[3] > cn->hgt))
			return (0);
		return (cn->has_caps && i_cn_bottom(i, cn, a));
	}
	i->shape = (t_obj *)obj;
	i->pos = i_pos(i);
	i->nor = get_cnnormal(cn, i->pos);
	normalize(&i->nor);
	return (1);
}

int	cn_intersect(t_intersect *i, t_obj *obj, int f)
{
	float	t_val;

	t_val = i->t;
	if (f == NO_UPDATE)
	{
		if (cn_judge_inter(i, obj, t_val) != 0)
			return (1);
	}
	else
	{
		if (cn_update_inter(i, obj, t_val) != 0)
			return (1);
	}
	return (0);
}