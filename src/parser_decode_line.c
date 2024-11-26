/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_decode_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:12:25 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/25 16:10:45 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parser.h"

int	decode_amb_lght(char *line, t_amb_light *amb_lght)
{
	int		i;
	char	**split_line;

	i = 0;
	split_line = ft_split(line, ' ');
	if (!split_line)
		return (MALLOC_ERROR);
	if (split_line[0] && split_line[1])
	{
		amb_lght->ratio = ft_atof(split_line[1]);
		if (amb_lght->ratio < 0 || amb_lght->ratio > 1)
		{
			free_array(split_line);
			return (AMBIENT_LIGHT_ERROR);
		}
	}
	else
	{
		free_array(split_line);
		return (AMBIENT_LIGHT_ERROR);
	}
	free_array(split_line);
	return (NO_ERROR);
}

int	decode_camera(char *line, t_camera *cmra)
{
	int		i;
	char	**split_line;

	i = 0;
	split_line = ft_split(line, ' ');
	if (!split_line)
		return (MALLOC_ERROR);
	if (split_line[0] && split_line[1] && split_line[2] && split_line[3] 
			&& split_line[4] && split_line[5] && split_line[6] && split_line[7])
	{
		cmra->origin[0] = ft_atof(split_line[1]);
		cmra->origin[1] = ft_atof(split_line[2]);
		cmra->origin[2] = ft_atof(split_line[3]);
		cmra->orientation[0] = ft_atof(split_line[4]);
		cmra->orientation[1] = ft_atof(split_line[5]);
		cmra->orientation[2] = ft_atof(split_line[6]);
		cmra->fov = ft_atoi(split_line[7]);
	}
	else
	{
		free_array(split_line);
		return (CAMERA_ERROR);
	}
	free_array(split_line);
	return (NO_ERROR);
}
