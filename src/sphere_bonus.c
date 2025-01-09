/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:55:03 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 18:00:09 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

int	get_t(t_intersect *i, float *a)
{
	float	discriminant;
	float	t[2];

	discriminant = sqr(a[1]) - 4.0f * a[0] * a[2];
	if (discriminant < 0)
		return (-1);
	t[0] = (-a[1] - sqrt(discriminant)) / (2.0f * a[0]);
	t[1] = (-a[1] + sqrt(discriminant)) / (2.0f * a[0]);
	if (t[0] > T_VALUE_MIN && t[0] < i->t && t[0] < t[1])
		i->t = t[0];
	else if (t[1] > T_VALUE_MIN && t[1] < i->t)
		i->t = t[1];
	else
		return (-1);
	a[0] = t[0];
	a[1] = t[1];
	return (0);
}

int	sp_intersect(t_intersect *i, t_obj *obj, int f)
{
	t_sp	*sp;
	t_ray	ray;
	t_vec3	oc;
	float	a[3];
	float	t_val;

	sp = (t_sp *)obj->elm;
	ray = i->ray;
	oc = vec3_sub(&ray.origin, &sp->center);
	a[0] = vec3_dot(&ray.direction, &ray.direction);
	a[1] = 2.0f * vec3_dot(&oc, &ray.direction);
	a[2] = vec3_dot(&oc, &oc) - sqr(sp->radius);
	if (get_t(i, a) == -1)
		return (0);
	t_val = 0.0f;
	if (f == YES_UPDATE)
		sp_update_inter(i, obj, t_val);
	return (1);
}

int	sp_update_inter(t_intersect *i, t_obj *obj, float t_val)
{
	i->shape = (t_obj *)obj;
	(void)t_val;
	i->pos = vec3_sum(i->ray.origin, vec3_mpl(i->ray.direction, i->t));
	i->nor = vec3_sub(&(i->pos), &(((t_sp *)i->shape->elm)->center));
	normalize(&i->nor);
	return (1);
}
