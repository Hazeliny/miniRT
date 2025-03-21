/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init4_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:49:17 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 12:43:34 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_point	init_point(float x, float y, float z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_rgb	init_rgb(int r, int g, int b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

void	init_texturef(char *s, t_obj *obj)
{
	int	i;

	if (ft_strlen(s) == 1 && !ft_isdigit(s[0]))
		terminate("bumf is incorrect..\n");
	check_point(s);
	check_extreme(s);
	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]) && s[i] != '.')
			terminate("bumf is incorrect..\n");
	obj->texture_f = ft_atof(s);
}

void	init_texture(t_obj **obj, char **ss)
{
	int		i;
	t_obj	*cur;

	i = 0;
	while (ss && ss[i])
		i++;
	if (i != 3)
		terminate("incorrect texture parameters..\n");
	cur = NULL;
	if (*obj)
	{
		cur = find_lstlast_obj(obj);
		cur->has_texture = true;
		if (!ft_strcmp(cur->typ, "sp"))
			init_texturef(ss[1], cur);
		if (validate_xpmfile(ss[2]) == -1)
			terminate("incorrect texture xpmfile..\n");
		cur->texture.path = ft_strdup(ss[2]);
	}
}
