/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:44:42 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/30 13:05:06 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/**
 * @brief	Frees a 2D array of strings
 * 
 * @param	arr	pointer to the array of strings
 * @return	void
 */
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

/**
 * @brief	Safe memory allocation function
 * 
 * @param	size	size of the memory to allocate
 * @return	void*	pointer to the allocated memory
 * @note	terminates the program if memory allocation fails
 */
void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		terminate(ERR_MEMO);
	return (ptr);
}
