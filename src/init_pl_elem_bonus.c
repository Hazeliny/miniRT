/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pl_elem_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:19:41 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 14:57:18 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	init_pl_p(char *s, t_pl *pl)
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
	pl->p = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
	free_array(arr);
}

void	init_pl_n_vec(char *s, t_pl *pl)
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
	pl->n_vec = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
	if ((pl->n_vec.x < -1 || pl->n_vec.x > 1) || \
		(pl->n_vec.y < -1 || pl->n_vec.y > 1) || \
		(pl->n_vec.x < -1 || pl->n_vec.x > 1))
		terminate(ERR_PARA);
	normalize(&(pl->n_vec));
	free_array(arr);
}

void	init_pl_rgb(char *s, t_pl *pl)
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
	pl->rgb = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
	if ((pl->rgb.r < 0 || pl->rgb.r > 255) || \
		(pl->rgb.g < 0 || pl->rgb.g > 255) || \
		(pl->rgb.b < 0 || pl->rgb.b > 255))
		terminate(ERR_PARA);
	free_array(arr);
}
