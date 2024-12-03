/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:40:27 by linyao            #+#    #+#             */
/*   Updated: 2024/12/03 23:00:22 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int ft_isspace(char *s)
{
    int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && \
			s[i] != '\v' && s[i] != '\f' && s[i] != '\r')
			return (1);
		i++;
	}
	return (0);
}

t_obj	*find_lstlast(t_obj **obj)
{
	t_obj	*last;

	if (!(*obj))
		return (*obj);
	last = *obj;
	while (last->next)
		last = last->next;
	return (last);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}