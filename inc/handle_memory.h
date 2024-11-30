/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:47:49 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/29 16:48:13 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_MEMORY_H
# define HANDLE_MEMORY_H

# include "miniRT.h"

void	free_simple(void **ptr);
void	free_array(char **doub);
void	*safe_malloc(size_t size);

#endif