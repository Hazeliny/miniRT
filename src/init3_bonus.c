/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:10:12 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 14:20:16 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	init_bumpf(char *s, t_obj *obj)
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
	obj->bump_f = ft_atof(s);
}

int	validate_xpmfile(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (len < 5 && ft_strncmp(path - 4, ".xpm", 4))
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

void	init_bump(t_obj **obj, char **ss)
{
	int		i;
	t_obj	*cur;

	i = 0;
	while (ss && ss[i])
		i++;
	if (i != 3)
		terminate("incorrect bump parameters..\n");
	cur = NULL;
	if (*obj)
	{
		cur = find_lstlast_obj(obj);
		cur->has_bump = true;
		if (!ft_strcmp(cur->typ, "sp"))
			init_bumpf(ss[1], cur);
		if (validate_xpmfile(ss[2]) == -1)
			terminate("incorrect bump xpmfile..\n");
		if (cur->bump.path)
			free(cur->bump.path);
		cur->bump.path = ft_strdup(ss[2]);
	}
}
