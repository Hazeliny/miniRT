/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_al_elem_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:04:08 by linyao            #+#    #+#             */
/*   Updated: 2024/12/27 12:26:03 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void    check_al_ratio(char *s)
{
    int i;

    i = 0;
    if (ft_strlen(s) == 1 && ft_isdigit(s[0]) != 0 && (s[0] < '0' || s[0] > '1'))
        terminate(ERR_PARA);
    if (ft_strlen(s) == 1 && !ft_isdigit(s[0]))
        terminate(ERR_PARA);
    check_point(s);
    while (s[i])
    {
        if (!ft_isdigit(s[i]) && s[i] != '.')
            terminate(ERR_PARA);
        i++;
    }
}

int init_al_rgb(char *s, t_al *al)
{
    char    **arr;
    int     i;

    i = 0;
    while (s[i])
    {
        if (s[i] == '.')
            terminate(ERR_PARA);
        i++;
    }
    check_commas(s);
    arr = ft_split(s, ',');
    if (!arr)
        terminate(ERR_PARA);
    i = 0;
    while (arr[i])
        i++;
    if (i != 3)
        terminate(ERR_PARA);
    al->color = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
    if ((al->color.r < 0 || al->color.r > 255) || \
        (al->color.g < 0 || al->color.g > 255) || \
        (al->color.b < 0 || al->color.b > 255))
        terminate(ERR_PARA);
    free_array(arr);
    return (0);
}