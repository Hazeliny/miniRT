/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:23:28 by linyao            #+#    #+#             */
/*   Updated: 2024/11/30 00:30:24 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_sp   *init_sp(char **ss)
{
    t_sp    *new_sp;
    int     i;

    i = 0;
    while (ss[i])
        i++;
    new_sp = ft_calloc(1, sizeof(t_sp));
    if (!new_sp)
        terminate(ERR_MEMO);
    assign_sp(ss, i, new_sp);
    return (new_sp);
}