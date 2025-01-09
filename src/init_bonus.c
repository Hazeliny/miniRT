/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:09:35 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 12:37:09 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	init_checkerboard(t_obj **obj, char **str)
{
	t_obj	*cur;
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i < 2)
		terminate("Invalid checkerboard input\n");
	cur = NULL;
	if (*obj)
	{
		cur = find_lstlast_obj(obj);
		cur->has_checkerboard = true;
		if (!ft_strcmp(cur->typ, "pl"))
			init_cb_scale(str[1], (t_pl *)cur->elm);
	}
}

static void	set_node_bool(t_obj *node)
{
	node->has_checkerboard = false;
	node->has_bump = false;
	node->has_texture = false;
}

void	init_obj(t_obj **obj, char **str, const char *type)
{
	t_obj	*node;

	node = ft_calloc_new(1, sizeof(t_obj));
	ft_strlcpy(node->typ, type, 3);
	node->next = NULL;
	init_vtable(node);
	if (!ft_strcmp(type, "sp"))
		node->elm = init_sp(str);
	else if (!ft_strcmp(type, "pl"))
		node->elm = init_pl(str);
	else if (!ft_strcmp(type, "cy"))
		node->elm = init_cy(str);
	else if (!ft_strcmp(type, "cn"))
		node->elm = init_cn(str);
	else
	{
		free(node);
		terminate("Unknown object type\n");
	}
	set_node_bool(node);
	if (*obj)
		(find_lstlast_obj(obj))->next = node;
	else
		(*obj) = node;
}

static void	init_obj_vtable(t_obj *cur)
{
	if (!ft_strcmp(cur->typ, "pl"))
	{
		cur->vtable->is_intersect = &pl_intersect;
		cur->vtable->update_inter = &pl_update_inter;
	}
	else if (!ft_strcmp(cur->typ, "sp"))
	{
		cur->vtable->is_intersect = &sp_intersect;
		cur->vtable->update_inter = &sp_update_inter;
	}
	else if (!ft_strcmp(cur->typ, "cy"))
	{
		cur->vtable->is_intersect = &cy_intersect;
		cur->vtable->update_inter = &cy_update_inter;
	}
	else if (!ft_strcmp(cur->typ, "cn"))
	{
		cur->vtable->is_intersect = &cn_intersect;
		cur->vtable->update_inter = &cn_update_inter;
	}
}

void	init_vtable(t_obj *obj)
{
	t_obj	*cur;

	cur = obj;
	cur->vtable = ft_calloc_new(1, sizeof(t_vtable));
	init_obj_vtable(cur);
	if (ft_strcmp(cur->typ, "pl") && ft_strcmp(cur->typ, "sp") && \
		ft_strcmp(cur->typ, "cy") && ft_strcmp(cur->typ, "cn"))
	{
		free(cur->vtable);
		free(cur);
		terminate("Unknown object type\n");
	}
}
