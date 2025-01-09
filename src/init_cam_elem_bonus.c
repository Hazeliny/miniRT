/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam_elem_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:19:03 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 14:41:20 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void	init_cam_pov(char *s, t_cam *cam)
{
	char	**arr;
	int		i;

	check_commas(s);
	arr = ft_split(s, ',');
	if (!arr)
		terminate(ERR_MEMO);
	i = -1;
	while (arr[++i])
	{
		check_negative(arr[i]);
		check_point(arr[i]);
		check_extreme(arr[i]);
	}
	if (i != 3)
		terminate(ERR_PARA);
	cam->pov = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
	free_array(arr);
}

void	init_cam_nvec(char *s, t_cam *cam)
{
	char	**arr;
	int		i;

	check_commas(s);
	arr = ft_split(s, ',');
	if (!arr)
		terminate(ERR_MEMO);
	i = -1;
	while (arr[++i])
	{
		check_negative(arr[i]);
		check_point(arr[i]);
	}
	if (i != 3)
		terminate(ERR_PARA);
	cam->n_vec = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
	if ((cam->n_vec.x < -1 || cam->n_vec.x > 1) || \
		(cam->n_vec.y < -1 || cam->n_vec.y > 1) || \
		(cam->n_vec.z < -1 || cam->n_vec.z > 1))
		terminate(ERR_PARA);
	normalize(&cam->n_vec);
	free_array(arr);
}

void	init_cam_fov(char *s, t_cam *cam)
{
	char	*tmp;
	char	*tmp1;
	int		i;

	tmp = ft_strdup(s);
	tmp1 = ft_strtrim(tmp, "\n");
	free(tmp);
	if (ft_strlen(tmp1) > 3)
		terminate(ERR_PARA);
	i = 0;
	while (tmp1[i])
	{
		if (!ft_isdigit(tmp1[i]))
			terminate(ERR_PARA);
		i++;
	}
	cam->fov = ft_atoi(tmp1);
	if (cam->fov > 180 || cam->fov < 0)
		terminate(ERR_PARA);
	free(tmp1);
}
