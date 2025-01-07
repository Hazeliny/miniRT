/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cn_elem_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:43:07 by linyao            #+#    #+#             */
/*   Updated: 2024/12/31 12:38:38 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void    init_cn_apex(char *s, t_cn *cn)
{
    char    **arr;
    int     i;

    check_commas(s);
    arr = ft_split(s, ',');
    if (!arr)
        terminate("fail to split cone's apex coordinate\n");
    i = 0;
    while (arr[i])
    {
        check_negative(arr[i]);
        check_point(arr[i]);
        check_extreme(arr[i]);
        i++;
    }
    if (i!= 3)
        terminate("incorrect apex coordinate\n");
    cn->apex = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    free_array(arr);
}

void    init_cn_axis(char *s, t_cn *cn)
{
    char    **arr;
    int     i;

    check_commas(s);
    arr = ft_split(s, ',');
    if (!arr)
        terminate("fail to split cone's axis coordinate\n");
    i = 0;
    while (arr[i])
    {
        check_negative(arr[i]);
        check_point(arr[i]);
        i++;
    }
    if (i!= 3)
        terminate("incorrect cone axis\n");
    cn->axis = init_point(ft_atof(arr[0]), ft_atof(arr[1]), ft_atof(arr[2]));
    if ((cn->axis.x < -1 || cn->axis.x > 1) || \
        (cn->axis.y < -1 || cn->axis.y > 1) || \
        (cn->axis.z < -1 || cn->axis.z > 1))
        terminate("cone's axis out of range\n");
//    normalize(&cn->axis);
    cn->axis = normalize_axis(cn);
    free_array(arr);
}

t_obj   *init_cn_surface(t_cn *cn)
{
    t_obj   *new;
    t_pl    *pl;

    pl = ft_calloc_new(1, sizeof(t_pl));
    pl->p = cn->center;
//    if (surface)
    pl->normal = vec3_mpl(cn->axis, -1);
//    else
//    {
//        pl->p = cn->apex;
//        pl->normal = cn->axis;
//    }
    pl->rgb = cn->rgb;
    new = ft_calloc_new(1, sizeof(t_obj));
    new->elm = pl;
    ft_strlcpy(new->typ, "pl", 3);
    init_vtable(new);
    return (new);
}

float   init_cn_float(char *s)
{
    int i;

    if (ft_strlen(s) == 1 && ft_isdigit(s[0]))
        return (ft_atof(s));
    check_point(s);
    check_extreme(s);
    i = -1;
    while (s[++i])
        if (!ft_isdigit(s[i]) && s[i] != '.')
            terminate("incorrect cone height or radius\n");
    return (ft_atof(s));
}

void    init_cn_rgb(char *s, t_cn *cn)
{
    char    **arr;
    int     i;

    i = -1;
    while (s[++i])
        if (s[i] == '.')
            terminate("cone rgb should not be decimal point\n");
    check_commas(s);
    arr = ft_split(s, ',');
    if (!arr)
        terminate("fail to split cone's rgb\n");
    i = 0;
    while (arr[i])
        i++;
    if (i!= 3)
        terminate("incorrect number of rgb parameters of cone\n");
    cn->rgb = init_rgb(ft_atoi(arr[0]), ft_atoi(arr[1]), ft_atoi(arr[2]));
    if ((cn->rgb.r < 0 || cn->rgb.r > 255) || \
        (cn->rgb.g < 0 || cn->rgb.g > 255) || \
        (cn->rgb.b < 0 || cn->rgb.b > 255))
        terminate("cone's rgb out of range\n");
    free_array(arr);
}