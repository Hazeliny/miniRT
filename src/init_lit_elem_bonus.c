/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lit_elem_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:57:10 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 14:47:27 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	init_lit_lsrc(char *s, t_lit *lit)
{
	char	**arr;
	int		i;

	check_commas(s);
	arr = ft_split(s, ',');
	if (!arr)
		terminate(ERR_MEMO);
	i = 0;
	while (arr[i])
	{
		check_negative(arr[i]);
		check_point(arr[i]);
		check_extreme(arr[i]);
		i++;
	}
	if (i != 3)
		terminate(ERR_PARA);
	lit->l_src = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
	free_array(arr);
}

void	check_lit_rbrt(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) == 1 && ft_isdigit(s[0]) && (s[0] < '0' || s[0] > '1'))
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

void	init_lit_color(char *s, t_lit *lit)
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
	lit->color = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
	if ((lit->color.r < 0 || lit->color.r > 255) || \
		(lit->color.g < 0 || lit->color.g > 255) || \
		(lit->color.b < 0 || lit->color.b > 255))
		terminate(ERR_PARA);
	free_array(arr);
}
