/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cleanings_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:03:44 by linyao            #+#    #+#             */
/*   Updated: 2024/12/27 12:25:32 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void    terminate(char *s)
{
    if (errno == 0)
        ft_putendl_fd(s, 2);
    else
        perror(s);
    exit(1);
}

void	free_sp(t_sp *sp)
{
	if (sp)
		free(sp);
	sp = NULL;
}

void	free_pl(t_pl *pl)
{
	if (pl)
		free(pl);
	pl = NULL;
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i++] = NULL;
	}
	free(arr);
	arr = NULL;
}