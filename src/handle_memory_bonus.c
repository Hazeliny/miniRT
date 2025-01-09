/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:44:42 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 18:34:36 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

static void	free_bm_tx(t_obj *obj)
{
	if (obj->bump.path)
		free(obj->bump.path);
	if (obj->texture.path)
		free(obj->texture.path);
	obj->bump.path = NULL;
	obj->texture.path = NULL;
	obj->has_bump = false;
	obj->has_texture = false;
}

void	free_obj(t_obj **objs)
{
	t_obj	*tmp;
	t_obj	*obj;

	if (!objs || !*objs)
		return ;
	obj = *objs;
	while (obj)
	{
		tmp = obj->next;
		if (!ft_strcmp(obj->typ, "sp"))
			free_sp((t_sp *)obj->elm);
		else if (!ft_strcmp(obj->typ, "pl"))
			free_pl((t_pl *)obj->elm);
		else if (!ft_strcmp(obj->typ, "cy"))
			free_cy((t_cy *)obj->elm);
		else if (!ft_strcmp(obj->typ, "cn"))
			free_cn((t_cn *)obj->elm);
		if (obj->vtable)
			free(obj->vtable);
		free_bm_tx(obj);
		obj->vtable = NULL;
		free(obj);
		obj = tmp;
	}
	*objs = NULL;
}

void	free_rt(t_rt *rt)
{
	if (rt)
	{
		if (rt->obj)
		{
			free_obj(&rt->obj);
			rt->obj = NULL;
		}
	}
}
