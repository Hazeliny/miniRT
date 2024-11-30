/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:59:33 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/29 23:54:28 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/**
 * @brief 	the function takes part in the check after all the possible
 *  objects have been checked, and::
 * - if the line is empty it returns EOF;
 * - if the line contains only spaces or tabs it returns NO_ERR,
 * - otherwise it returns ERR
 * 
 * @param	line	pointer to the line to check
 * @return	int		error code
 */
static int	check_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (EOF);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\0')
		return (ERR);
	return (NO_ERR);
}

int	verify_line_elem(char *line)
{
	char	*str;

	str = ft_strtrim(line, " ");
	if (!t_isalpha(*str))
		terminate(ERR_FILE_CONTENT);
	else
	{
		while (ft_isalpha(*str))
			str++;
	}
	if (*str == '\0')
		terminate(ERR_FILE_CONTENT);
	while (*str)
	{
		if (*str != ' ' && *str != '-' && *str != '.' && *str != ',' \
				&& *str != '\n' && !ft_isdigit(*str))
			terminate(ERR_FILE_CONTENT);
		str++;
	}
	free(str);
	return (0);
}

void	verify_id(char *s, char **ss, t_rt *rt)
{
	if (!ft_strncmp(s, "A", 2))
		init_al(rt, ss);
	else if (!ft_strncmp(s, "C", 2))
		init_cam(rt, ss);
	else if (!ft_strncmp(s, "L", 2))
		init_lit(rt, ss);
	else if (!ft_strncmp(s, "sp", 3))
		init_obj(&(rt->obj), ss, "sp");
	else if (!ft_strncmp(s, "pl", 3))
		init_obj(&(rt->obj), ss, "pl");
	else if (!ft_strncmp(s, "cy", 3))
		init_obj(&(rt->obj), ss, "cy");
	else
		terminate(ERR_ID);
}

/**
 * @brief	Decodes the line and calls the appropriate function
 * 
 * @param	line	pointer to the line to decode
 * @param	rt		pointer to the main structure
 * @return	int		error code
 */
void	decode_line(char *line, t_rt *rt)
{
	char	**arr;
	
	if (!line || !ft_isspace(line))
		return (0);
	verify_line_elem(line);
	arr = ft_split(line, ' ');
	if (!arr)
		terminate(ERR_MEMO);
	verify_id(arr[0], arr, rt);
	free_array(arr);
/*	
	if (line[0] == 'A')
		decode_al(line, rt);
	else if (line[0] == 'C')
		decode_cam(line, rt);
	else if (line[0] == 'L')
		decode_lit(line, rt);
	else if (ft_strnstr(line, "sp", 2) || ft_strnstr(line, "pl", 2)
			|| ft_strnstr(line, "cy", 2))
	{
		init_obj(rt);
		if (ft_strnstr(line, "sp", 2))
			decode_sp(line, rt);
		else if (ft_strnstr(line, "pl", 2))
			decode_pl(line, rt);
		else if (ft_strnstr(line, "cy", 2))
			decode_cy(line, rt);
	}
	else
		return (check_line(line));
*/
}

int	check_filename(char *fn)
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

void	read_map_file(t_rt *rt, char *str)
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

/**
 * @brief	Parses the file
 * 
 * @param	rt			pointer to the main structure
 * @param	file_name	name of the file to parse
 * @return	int			error code
 */
void	parse(t_rt *rt, const char *file_name)
{
	if (check_filename(file_name) != 0)
		terminate(ERR_FILENAME);
	read_map_file(rt, file_name);
	
	
}

