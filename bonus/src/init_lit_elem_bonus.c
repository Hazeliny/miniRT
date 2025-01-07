/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lit_elem_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:57:10 by linyao            #+#    #+#             */
/*   Updated: 2024/12/27 12:26:50 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"
// hecho
//    lit->l_src = init_point(ft_atof("-300.0"), ft_atof("10.0"), ft_atof("100.0"));
// s is a one-dimensional array, presenting the coordinates of lit-src eg: -40.0,50.0,0.0
// firstly check errors in parameters such as commas&digits&non-digits in lit-src
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// looping check every element in the 2D array as follows:
// check errors: negative sign: 0.-0 or 0-.0 or -
// check errors: .0 or 0.0.0 or ab.0 or 0.ab
// control the maximal 3 decimals, eg: throw error when it's 0.123456
// control the maximal 10 integer digits part of floats, eg: throw error when it's 12345678901.11
// if the splitting result above doesn't equal to 3 elements, eg: throw error when it's 0.0,0.0,20.6,1.0,0.2
// Done as follows: initialize lit-src and free. I've realized the following, but make sure if ft_atof works without glitching
void    init_lit_lsrc(char *s, t_lit *lit)
{
    char    **arr;
    int     i;

    check_commas(s);
    arr = ft_split(s, ',');
    if (!arr)
        terminate(ERR_MEMO);
    i = 0;
    while (arr[i])
    {
        check_negative(arr[i]);
        check_point(arr[i]);
        check_extreme(arr[i]);
        i++;
    }
    if (i != 3)
        terminate(ERR_PARA);
    lit->l_src = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    free_array(arr);
}
//hecho
void    check_lit_rbrt(char *s)
{
    int i;

    i = 0;
    if (ft_strlen(s) == 1 && ft_isdigit(s[0]) && (s[0] < '0' || s[0] > '1'))
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
// hecho
//    arr = ft_split("255,255,255", ',');// datos para probar temporalmente!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// s is a one-dimensional array, presenting the lit-color eg: 255,255,255
// firstly looping check if exists ".", once it does, throw error. i.e. check if the 3 elements in the array are integers
// then check errors in parameters such as commas&digits&non-digits in lit-color
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// count the number of the 2D array's elements, if it isnot 3(eg: 255,255,255,255), throw error
void    init_lit_color(char *s, t_lit *lit)
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
    lit->color = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
    if ((lit->color.r < 0 || lit->color.r > 255) || \
        (lit->color.g < 0 || lit->color.g > 255) || \
        (lit->color.b < 0 || lit->color.b > 255))
        terminate(ERR_PARA);
    free_array(arr);
}