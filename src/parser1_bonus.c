/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:05:48 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 12:10:53 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

int	verify_line_elem(char *line)
{
	char	*str;
	char	*s;

	str = ft_strtrim(line, " ");
	s = str;
	if (!ft_isalpha(*str))
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
				&& *str != '\n' && !ft_isalnum(*str) && *str != '/')
			terminate(ERR_FILE_CONTENT);
		str++;
	}
	free(s);
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
	else if (!ft_strncmp(s, "cn", 3))
		init_obj(&(rt->obj), ss, "cn");
	else if (!ft_strncmp(s, "cb", 3))
		init_checkerboard(&(rt->obj), ss);
	else if (!ft_strncmp(s, "bm", 3))
		init_bump(&(rt->obj), ss);
	else if (!ft_strncmp(s, "tx", 3))
		init_texture(&(rt->obj), ss);
	else
		terminate(ERR_ID);
}

void	decode_line(char *line, t_rt *rt)
{
	char	**arr;

	if (!line || !ft_isspace_str(line))
		return ;
	verify_line_elem(line);
	arr = ft_split(line, ' ');
	if (!arr)
		terminate(ERR_MEMO);
	verify_id(arr[0], arr, rt);
	free_array(arr);
}
