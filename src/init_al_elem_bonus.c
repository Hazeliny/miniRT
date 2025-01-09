/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_al_elem_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:04:08 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 14:34:58 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	check_al_ratio(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) == 1 && ft_isdigit(s[0]) != 0 && \
					(s[0] < '0' || s[0] > '1'))
		terminate(ERR_PARA);
	if (ft_strlen(s) == 1 && !ft_isdigit(s[0]))
		terminate(ERR_PARA);
	check_point(s);
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '.')
			terminate(ERR_PARA);
		i++;
	}
}

static void	check_al_color(t_rgb color)
{
	if ((color.r < 0 || color.r > 255) || \
		(color.g < 0 || color.g > 255) || \
		(color.b < 0 || color.b > 255))
		terminate(ERR_PARA);
}

int	init_al_rgb(char *s, t_al *al)
{
	char	**arr;
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '.')
			terminate(ERR_PARA);
		i++;
	}
	check_commas(s);
	arr = ft_split(s, ',');
	if (!arr)
		terminate(ERR_PARA);
	i = 0;
	while (arr[i])
		i++;
	if (i != 3)
		terminate(ERR_PARA);
	al->color = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
	check_al_color(al->color);
	free_array(arr);
	return (0);
}
