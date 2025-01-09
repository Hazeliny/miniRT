/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:31:49 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 18:31:55 by linyao           ###   ########.fr       */
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
