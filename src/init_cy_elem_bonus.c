/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cy_elem_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:15:12 by linyao            #+#    #+#             */
/*   Updated: 2024/12/27 12:26:37 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"
//hecho
// s is a one-dimensional array, presenting the coordinates of cy-center eg: 50.0,0.0,20.6
// firstly check errors in parameters such as commas&digits&non-digits in cy-center
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// looping check every element in the 2D array as follows:
// check errors: negative sign: 0.-0 or 0-.0 or -
// check errors: .0 or 0.0.0 or ab.0 or 0.ab
// control the maximal 3 decimals, eg: throw error when it's 0.123456
// control the maximal 10 integer digits part of floats, eg: throw error when it's 12345678901.11
// if the splitting result above doesn't equal to 3 elements, eg: throw error when it's 0.0,0.0,20.6,1.0,0.2
// Done as follows: initialize cy-center and free. I've realized the following, but make sure if ft_atof works without glitching
void    init_cy_center(char *s, t_cy *cy)
{
//    cy->center = init_point(ft_atof("20.0"), ft_atof("-10.0"), ft_atof("20.6"));
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
    if (i!= 3)
        terminate(ERR_PARA);
    cy->center = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    free_array(arr);
}
//hecho
// s is a one-dimensional array, presenting the coordinates of cy-axis eg: 0.0,0.0,1.0
// firstly check errors in parameters such as commas&digits&non-digits in cy-axis
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// looping check every element in the 2D array as follows:
// check errors: negative sign: 0.-0 or 0-.0 or -
// check errors: .0 or 0.0.0 or ab.0 or 0.ab
// control the maximal 3 decimals, eg: throw error when it's 0.123456
// if the splitting result above doesn't equal to 3 elements, eg: throw error when it's 0.0,0.0,1.0,0.0
// Done as follows: initialize cy-axis and free. I've realized the following, but make sure if ft_atof works without glitching
void    init_cy_axis(char *s, t_cy *cy)
{
//    cy->axis = init_point(ft_atof("0.5"), ft_atof("1"), ft_atof("0.5"));
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
        i++;
    }
    if (i!= 3)
        terminate(ERR_PARA);
    cy->axis = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    if ((cy->axis.x < -1 || cy->axis.x > 1) || \
        (cy->axis.y < -1 || cy->axis.y > 1) || \
        (cy->axis.z < -1 || cy->axis.z > 1))
        terminate(ERR_PARA);
    normalize(&cy->axis);
    free_array(arr);
}
//hecho
// s is a one-dimensional array, presenting the cy-diameter or cy-hgt eg: 14.2
// firstly check if it is digit 
// check errors: .0 or 0.0.0 or ab.0 or 0.ab
// control the maximal 3 decimals, eg: throw error when it's 0.123456
// control the maximal 10 integer digits part of floats, eg: throw error when it's 12345678901.11
// iterate the cy-diameter or cy-hgt array and check if there is non-digit or non-'.'(eg: 1a.6c). If there is, throw error
float   init_cy_float(char *s)
{
    int i;

    if (ft_strlen(s) == 1 && ft_isdigit(s[0]))
        return (ft_atof(s));
    check_point(s);
    check_extreme(s);
    i = -1;
    while (s[++i])
        if (!ft_isdigit(s[i]) && s[i] != '.')
            terminate(ERR_PARA);
    return (ft_atof(s));
}
//hecho
// s is a one-dimensional array, presenting the cy-rgb eg: 10,0,255
// firstly looping check if exists ".", once it does, throw error. i.e. check if the 3 elements in the array are integers
// then check errors in parameters such as commas&digits&non-digits in cy-rgb
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// count the number of the 2D array's elements, if it isnot 3(eg: 10,0,255,255), throw error
void    init_cy_rgb(char *s, t_cy *cy)
{
//    cy->rgb = init_rgb(ft_atoi("0"), ft_atoi("200"), ft_atoi("255"));
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
    if (i!= 3)
        terminate(ERR_PARA);
    cy->rgb = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
    if ((cy->rgb.r < 0 || cy->rgb.r > 255) || \
        (cy->rgb.g < 0 || cy->rgb.g > 255) || \
        (cy->rgb.b < 0 || cy->rgb.b > 255))
        terminate(ERR_PARA);
    free_array(arr);
}