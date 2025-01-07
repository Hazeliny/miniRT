/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:19:03 by linyao            #+#    #+#             */
/*   Updated: 2024/12/25 19:18:36 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
//hecho
// s is a one-dimensional array, presenting the coordinates of cam-pov eg: -50.0,0,20
// firstly check errors in parameters such as commas&digits&non-digits in cam-pov
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// looping check every element in the 2D array as follows:
// check errors: negative sign: 0.-0 or 0-.0 or -
// check errors: .0 or 0.0.0 or ab.0 or 0.ab
// control the maximal 3 decimals, eg: throw error when it's 0.123456
// control the maximal 10 integer digits part of floats, eg: throw error when it's 12345678901.11
// if the splitting result above doesn't equal to 3 elements, eg: throw error when it's 0.0,0.0,20.6,1.0,0.2
// Done as follows: initialize cam-pov and free. I've realized the following, but make sure if ft_atof works without glitching
void    init_cam_pov(char *s, t_cam *cam)
{
//    cam->pov = init_point(ft_atof("-300.0"), ft_atof("0.0"), ft_atof("0.0"));
    char    **arr;
    int     i;
    
    check_commas(s);
    arr = ft_split(s, ',');
    if (!arr)
        terminate(ERR_MEMO);
    i = -1;
    while (arr[++i])
    {
        check_negative(arr[i]);
        check_point(arr[i]);
        check_extreme(arr[i]);
    }
    if (i != 3)
        terminate(ERR_PARA);
    cam->pov = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    free_array(arr);
}
//hecho
// s is a one-dimensional array, presenting the coordinates of cam-nvec eg: 0.0,0.0,1.0
// firstly check errors in parameters such as commas&digits&non-digits in cam-nvec
// split x, y, z with ',' then put them into a two-dimensional array (char **arr). Attention: free it at last!
// looping check every element in the 2D array as follows:
// check errors: negative sign: 0.-0 or 0-.0 or -
// check errors: .0 or 0.0.0 or ab.0 or 0.ab
// control the maximal 3 decimals, eg: throw error when it's 0.123456
// if the splitting result above doesn't equal to 3 elements, eg: throw error when it's 0.0,0.0,1.0,0.0
// Done as follows: initialize cam-nvec and free. I've realized the following, but make sure if ft_atof works without glitching
void    init_cam_nvec(char *s, t_cam *cam)
{
    cam->n_vec = init_point(ft_atof("1.0"), ft_atof("0.0"), ft_atof("0.0"));
    
    char    **arr;
    int     i;

    check_commas(s);
    arr = ft_split(s, ',');
    if (!arr)
        terminate(ERR_MEMO);
    i = -1;
    while (arr[++i])
    {
        check_negative(arr[i]);
        check_point(arr[i]);
    }
    if (i != 3)
        terminate(ERR_PARA);
    cam->n_vec = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    if ((cam->n_vec.x < -1 || cam->n_vec.x > 1) || \
        (cam->n_vec.y < -1 || cam->n_vec.y > 1) || \
        (cam->n_vec.z < -1 || cam->n_vec.z > 1))
        terminate(ERR_PARA);
    normalize(&cam->n_vec);
    free_array(arr);
}
//hecho
void    init_cam_fov(char *s, t_cam *cam)
{
    char    *tmp;
    char    *tmp1;
    int     i;

    tmp = ft_strdup(s);
    tmp1 = ft_strtrim(tmp, "\n");
    free(tmp);
    if (ft_strlen(tmp1) > 3)
        terminate(ERR_PARA);
    i = 0;
    while (tmp1[i])
    {
        if (!ft_isdigit(tmp1[i]))
            terminate(ERR_PARA);
        i++;
    }
    cam->fov = ft_atoi(tmp1);
    if (cam->fov > 180 || cam->fov < 0)
        terminate(ERR_PARA);
    free(tmp1);
}