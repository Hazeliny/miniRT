/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:44:42 by linyao            #+#    #+#             */
/*   Updated: 2024/12/18 23:24:57 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	free_cy_topbottom(t_obj *tb)
{
	if (!tb)
		return ;
	if (tb->elm)
	{
		free(tb->elm);
		tb->elm = NULL;
	}
	if (tb->vtable)
	{
		free(tb->vtable);
		tb->vtable = NULL;
	}
	free(tb);
	tb = NULL;
}

void	free_cy(t_cy *cy)
{
	if (cy)
	{
		if (cy->top)
		{
			free_cy_topbottom(cy->top);
			cy->top = NULL;
		}
		if (cy->bottom)
		{
			free_cy_topbottom(cy->bottom);
			cy->bottom = NULL;
		}
		free(cy);
		cy = NULL;
	}
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
		if (obj->vtable)
		{
			free(obj->vtable);
			obj->vtable = NULL;
		}
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