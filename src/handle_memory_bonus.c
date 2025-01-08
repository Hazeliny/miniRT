/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:44:42 by linyao            #+#    #+#             */
/*   Updated: 2025/01/06 13:57:24 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

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

void	free_cn_bottom(t_obj *b)
{
	if (!b)
		return ;
	if (b->elm)
	{
		free(b->elm);
		b->elm = NULL;
	}
	if (b->vtable)
	{
		free(b->vtable);
		b->vtable = NULL;
	}
	free(b);
	b = NULL;
}

void	free_cn(t_cn *cn)
{
	if (cn)
	{
		if (cn->bottom)
		{
			free_cn_bottom(cn->bottom);
			cn->bottom = NULL;
		}
		free(cn);
		cn = NULL;
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
		else if (!ft_strcmp(obj->typ, "cn"))
			free_cn((t_cn *)obj->elm);
		if (obj->vtable)
			free(obj->vtable);
		if (obj->bump.path)
			free(obj->bump.path);
		if (obj->texture.path)
			free(obj->texture.path);
		obj->vtable = NULL;
		obj->bump.path = NULL;
		obj->texture.path = NULL;
		obj->has_bump = false;
		obj->has_texture = false;
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