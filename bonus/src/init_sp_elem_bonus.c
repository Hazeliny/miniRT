/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sp_elem_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:17:34 by linyao            #+#    #+#             */
/*   Updated: 2025/01/05 11:22:18 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"
//hecho
// s is a one-dimensional array, presenting the coordinates of sp-center eg: 0.0,0.0,20.6
// firstly check errors in parameters such as commas&digits&non-digits in sp-center
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// looping check every element in the 2D array as follows:
// check errors: negative sign: 0.-0 or 0-.0 or -
// check errors: .0 or 0.0.0 or ab.0 or 0.ab
// control the maximal 3 decimals, eg: throw error when it's 0.123456
// control the maximal 10 integer digits part of floats, eg: throw error when it's 12345678901.11
// if the splitting result above doesn't equal to 3 elements, eg: throw error when it's 0.0,0.0,20.6,1.0,0.2
// Done as follows: initialize sp-center and free. I've realized the following, but make sure if ft_atof works without glitching
void    init_sp_center(char *s, t_sp *sp)
{
//    sp->center = init_point(25.0, 50.0, 20.6);
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
    sp->center = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    free_array(arr);
}

void    init_sp_radius(char *s, t_sp *sp)
{
    int i;

    if(ft_strlen(s) == 1 && !ft_isdigit(s[0]))
        terminate(ERR_PARA);
    check_point(s);
    check_extreme(s);
    i = -1;
    while (s[++i])
        if (!ft_isdigit(s[i]) && s[i] != '.')
            terminate(ERR_PARA);
    sp->radius = ft_atof(s) / 2;
}
//hecho
// s is a one-dimensional array, presenting the sp-rgb eg: 10,0,255
// firstly looping check if exists ".", once it does, throw error. i.e. check if the 3 elements in the array are integers
// then check errors in parameters such as commas&digits&non-digits in sp-rgb
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// count the number of the 2D array's elements, if it isnot 3(eg: 10,0,255,255), throw error
void    init_sp_rgb(char *s, t_sp *sp)
{
//    sp->rgb = init_rgb(ft_atoi("10"), ft_atoi("0"), ft_atoi("255"));
    char    **arr;
    int     i;

    i = -1;
    while (s[++i])
        if (s[i] == '.')
            terminate(ERR_PARA);
    check_commas(s);
    arr = ft_split(s, ',');
    if (!arr)
        terminate(ERR_MEMO);
    i = 0;
    while (arr[i])
        i++;
    if (i != 3)
        terminate(ERR_PARA);
    sp->rgb = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
    if ((sp->rgb.r < 0 || sp->rgb.r > 255) || \
        (sp->rgb.g < 0 || sp->rgb.g > 255) || \
        (sp->rgb.b < 0 || sp->rgb.b > 255))
        terminate(ERR_PARA);
    free_array(arr);
}