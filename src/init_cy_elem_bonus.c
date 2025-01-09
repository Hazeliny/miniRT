/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cy_elem_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:15:12 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 16:26:15 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	init_cy_center(char *s, t_cy *cy)
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
	cy->center = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
	free_array(arr);
}

void	init_cy_axis(char *s, t_cy *cy)
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
		i++;
	}
	if (i != 3)
		terminate(ERR_PARA);
	cy->axis = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
	if ((cy->axis.x < -1 || cy->axis.x > 1) || \
		(cy->axis.y < -1 || cy->axis.y > 1) || \
		(cy->axis.z < -1 || cy->axis.z > 1))
		terminate(ERR_PARA);
	normalize(&cy->axis);
	free_array(arr);
}

float	init_cy_float(char *s)
{
	int	i;

	if (ft_strlen(s) == 1 && ft_isdigit(s[0]))
		return (ft_atof(s));
	check_point(s);
	check_extreme(s);
	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]) && s[i] != '.')
			terminate(ERR_PARA);
	return (ft_atof(s));
}

void	init_cy_rgb(char *s, t_cy *cy)
{
	char	**arr;
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == '.')
			terminate(ERR_PARA);
	check_commas(s);
	arr = ft_split(s, ',');
	if (!arr)
		terminate(ERR_MEMO);
	i = 0;
	while (arr[i])
		i++;
	if (i != 3)
		terminate(ERR_PARA);
	cy->rgb = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
	if ((cy->rgb.r < 0 || cy->rgb.r > 255) || \
		(cy->rgb.g < 0 || cy->rgb.g > 255) || \
		(cy->rgb.b < 0 || cy->rgb.b > 255))
		terminate(ERR_PARA);
	free_array(arr);
}
