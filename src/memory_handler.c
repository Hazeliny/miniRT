/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpietrza <mpietrza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:44:42 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/25 16:10:54 by mpietrza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	free_simple(void **ptr)
{
	if (ptr && *ptr)
		free(*ptr);
	*ptr = NULL;
	return ;
}

void	free_array(char **arr)
{
	int	size;

	size = 0;
	if (!arr)
		return ;
	while (arr[size])
		++size;
	while (size > 0)
		free_simple((void **)&arr[--size]);
	free_simple((void **)&arr);
}
