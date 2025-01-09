/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:59:33 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 12:09:59 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

int	check_filename(const char *fn)
{
	int	i;

	if (!fn)
		return (1);
	i = ft_strlen(fn);
	if (i < 4)
		return (1);
	if (fn[i - 3] != '.' || fn[i - 2] != 'r' || fn[i - 1] != 't')
		return (1);
	return (0);
}

void	read_map_file(t_rt *rt, const char *str)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		terminate(ERR_OPEN);
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, " \n");
		decode_line(tmp, rt);
		free(line);
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
}

void	parse(t_rt *rt, const char *file_name)
{
	if (check_filename(file_name) != 0)
		terminate(ERR_FILENAME);
	read_map_file(rt, file_name);
	if (!rt->n_al || !rt->n_cam || !rt->n_lit)
		terminate(ERR_ACL);
}
