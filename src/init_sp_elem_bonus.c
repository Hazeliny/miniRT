/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sp_elem_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:17:34 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 16:12:45 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	init_sp_center(char *s, t_sp *sp)
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
	sp->center = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
	free_array(arr);
}

void	init_sp_radius(char *s, t_sp *sp)
{
	int	i;

	if (ft_strlen(s) == 1 && !ft_isdigit(s[0]))
		terminate(ERR_PARA);
	check_point(s);
	check_extreme(s);
	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]) && s[i] != '.')
			terminate(ERR_PARA);
	sp->radius = ft_atof(s) / 2;
}

void	init_sp_rgb(char *s, t_sp *sp)
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
	sp->rgb = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
	if ((sp->rgb.r < 0 || sp->rgb.r > 255) || \
		(sp->rgb.g < 0 || sp->rgb.g > 255) || \
		(sp->rgb.b < 0 || sp->rgb.b > 255))
		terminate(ERR_PARA);
	free_array(arr);
}
