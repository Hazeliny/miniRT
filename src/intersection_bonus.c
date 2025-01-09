/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:31:02 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 17:40:57 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_vec3	get_spnormal(t_sp *sp, t_vec3 vec)
{
	t_vec3	tmp;

	tmp = vec3_sub(&sp->center, &vec);
	normalize(&tmp);
	return (tmp);
}

t_vec3	get_cnnormal(t_cn *cn, t_vec3 vec)
{
	t_vec3	v;
	t_vec3	proj_axis;
	t_vec3	normal;
	float	dp;

	v = vec3_sub(&vec, &cn->apex);
	dp = vec3_dot(&v, &cn->axis);
	proj_axis = vec3_mpl(cn->axis, dp);
	normal = vec3_sub(&v, &proj_axis);
	normalize(&normal);
	return (normal);
}

static t_vec3	get_cur_sp_normal(t_intersect *i, t_sp *sp)
{
	if (i->shape->has_bump || i->shape->has_texture)
		return (i->nor);
	else
		return (get_spnormal(sp, i_pos(i)));
}

t_vec3	get_normal_inter(t_intersect *i)
{
	t_pl	*pl;
	t_sp	*sp;
	t_cy	*cy;
	t_cn	*cn;

	if (i->shape->typ[0] == 'p' && i->shape->typ[1] == 'l')
	{
		pl = (t_pl *)(i->shape->elm);
		return (pl->normal);
	}
	else if (i->shape->typ[0] == 's' && i->shape->typ[1] == 'p')
	{
		sp = (t_sp *)(i->shape->elm);
		return (get_cur_sp_normal(i, sp));
	}
	else if (i->shape->typ[0] == 'c' && i->shape->typ[1] == 'y')
	{
		cy = (t_cy *)(i->shape->elm);
		return (get_cynormal(cy, i_pos(i)));
	}
	else
	{
		cn = (t_cn *)(i->shape->elm);
		return (get_cnnormal(cn, i_pos(i)));
	}
}

bool	obj_intersect(t_intersect *i, t_obj **obj)
{
	t_obj	*cur;
	bool	f;

	cur = *obj;
	f = false;
	while (cur)
	{
		if (!ft_strcmp(cur->typ, "pl") || !ft_strcmp(cur->typ, "sp") \
			|| !ft_strcmp(cur->typ, "cy") || !ft_strcmp(cur->typ, "cn"))
			if (cur->vtable->is_intersect(i, cur, YES_UPDATE))
				f = true;
		cur = cur->next;
	}
	return (f);
}
