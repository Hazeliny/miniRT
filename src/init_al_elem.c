/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_al_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:04:08 by linyao            #+#    #+#             */
/*   Updated: 2024/11/30 22:15:34 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void    check_al_ratio(char *s)
{
    int i;

    i = 0;
    if (ft_strlen(s) == 1 && ft_isdigit(s[0]) != 0 && (s[0] < '0' || s[0] > '1'))
        terminate(ERR_PARA);
    if (ft_strlen(s) == 1 && ft_isdigit(s[0]))
        return ;
    check_point(s); //will be realized in init_sp_center function ???
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
// s is a one-dimensional array, presenting the al-rgb eg: 255,255,255
// firstly looping check if exists ".", once it does, throw error. i.e. check if the 3 elements in the array are integers
// then check errors in parameters such as commas&digits&non-digits in al-rgb
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// count the number of the 2D array's elements, if it isnot 3(eg: 255,255,255,255), throw error
    al->color = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
    if ((al->color.r < 0 || al->color.r > 255) || \
        (al->color.g < 0 || al->color.g > 255) || \
        (al->color.b < 0 || al->color.b > 255))
        terminate(ERR_PARA);
    free_array(arr);
    return (0);
}