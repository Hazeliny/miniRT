/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pl_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:19:41 by linyao            #+#    #+#             */
/*   Updated: 2024/11/30 16:46:39 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void    init_pl_p(char *s, t_pl *pl)
{
    char    **arr;
    // s is a one-dimensional array, presenting the coordinates of pl-p eg: 0.0,0.0,-10.0
    // firstly check errors in parameters such as commas&digits&non-digits in pl-p
    // split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
    // looping check every element in the 2D array as follows:
    // check errors: negative sign: 0.-0 or 0-.0 or -
    // check errors: .0 or 0.0.0 or ab.0 or 0.ab
    // control the maximal 3 decimals, eg: throw error when it's 0.123456
    // control the maximal 10 integer digits part of floats, eg: throw error when it's 12345678901.11
    // if the splitting result above doesn't equal to 3 elements, eg: throw error when it's 0.0,0.0,20.6,1.0,0.2
    // Done as follows: initialize pl-ponit and free. I've realized the following, but make sure if ft_atof works without glitching
    pl->p = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    free_array(arr);
}

void    init_pl_n_vec(char *s, t_pl *pl)
{
    char    **arr;
    // s is a one-dimensional array, presenting the pl-n_vec eg: 0.0,1.0,0.0
    // firstly check errors in parameters such as commas&digits&non-digits in pl-n_vec
    // split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
    // looping check every element in the 2D array as follows:
    // check errors: negative sign: 0.-0 or 0-.0 or -
    // check errors: .0 or 0.0.0 or ab.0 or 0.ab
    // control the maximal 3 decimals, eg: throw error when it's 0.123456
    // if the splitting result above doesn't equal to 3 elements, eg: throw error when it's 0.0,0.0,20.6,1.0,0.2
    pl->n_vec = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    if ((pl->n_vec.x < -1 || pl->n_vec.x > 1) || \
        (pl->n_vec.y < -1 || pl->n_vec.y > 1) || \
        (pl->n_vec.x < -1 || pl->n_vec.x > 1))
        terminate(ERR_PARA);
    normalize(&(pl->n_vec));
    free_array(arr);
}

void    init_pl_rgb(char *s, t_pl *pl)
{
    char    **arr;
    // s is a one-dimensional array, presenting the pl-rgb eg: 0,0,255
    // firstly looping check if exists ".", once it does, throw error. i.e. check if the 3 elements in the array are integers
    // then check errors in parameters such as commas&digits&non-digits in pl-rgb
    // split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
    // count the number of the 2D array's elements, if it isnot 3(eg: 10,0,255,255), throw error
    pl->rgb = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
    if ((pl->rgb.r < 0 || pl->rgb.r > 255) || \
        (pl->rgb.g < 0 || pl->rgb.g > 255) || \
        (pl->rgb.b < 0 || pl->rgb.b > 255))
        terminate(ERR_PARA);
    free_array(arr);
}