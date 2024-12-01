/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:44:42 by mpietrza          #+#    #+#             */
/*   Updated: 2024/12/01 18:41:07 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	free_sp(t_sp *sp)
{
	if (sp)
		free(sp);
}

void	free_pl(t_pl *pl)
{
	if (pl)
		free(pl);
}

void	free_cy(t_cy *cy)
{
	if (cy)
	{
		if (cy->top.elm)
			free(cy->top.elm);
		if (cy->bottom.elm)
			free(cy->bottom.elm);
		free(cy);
	}
}

void	free_obj(t_obj *obj)
{
	t_obj	*tmp;

	while (obj)
	{
		tmp = obj->next;
		if (!ft_strcmp(&obj->typ, "sp"))
			free_sp((t_sp *)obj->elm);
		else if (!ft_strcmp(&obj->typ, "pl"))
			free_pl((t_pl *)obj->elm);
		else if (!ft_strcmp(&obj->typ, "cy"))
			free_cy((t_cy *)obj->elm);
		free(obj);
		obj = tmp;
	}
}

void	free_rt(t_rt *rt)
{	
	if (rt)
	{
		if (rt->obj)
		{
			free_obj(rt->obj);
			rt->obj = NULL;
		}
	}
}