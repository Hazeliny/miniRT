/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:23:28 by linyao            #+#    #+#             */
/*   Updated: 2024/12/15 19:47:15 by linyao           ###   ########.fr       */
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
    new_sp = ft_calloc_new(1, sizeof(t_sp));
    if (!new_sp)
        terminate(ERR_MEMO);
    if (i != 4)
        terminate(ERR_ARGV);
    init_sp_center(ss[1], new_sp);
    init_sp_radius(ss[2], new_sp);
    init_sp_rgb(ss[3], new_sp);
    return (new_sp);
}

t_pl    *init_pl(char **ss)
{
    t_pl    *new_pl;
    int     i;

    i = 0;
    while (ss[i])
        i++;
    new_pl = ft_calloc_new(1, sizeof(t_pl));
    if (!new_pl)
        terminate(ERR_MEMO);
    if (i != 4)
        terminate(ERR_ARGV);
    init_pl_p(ss[1], new_pl);
    init_pl_n_vec(ss[2], new_pl);
    init_pl_rgb(ss[3], new_pl);
    new_pl->normal = get_plnormal(new_pl->n_vec);
    return (new_pl);
}

t_cy    *init_cy(char **ss)
{
    t_cy    *new_cy;
    int     i;

    i = 0;
    while (ss[i])
        i++;
    new_cy = ft_calloc_new(1, sizeof(t_cy));
    if (!new_cy)
        terminate(ERR_MEMO);
    if (i != 6)
        terminate(ERR_ARGV);
    init_cy_center(ss[1], new_cy);
    init_cy_axis(ss[2], new_cy);
    new_cy->radius = init_cy_float(ss[3]) / 2;
    new_cy->hgt = init_cy_float(ss[4]);
    init_cy_rgb(ss[5], new_cy);
    new_cy->top = init_surface(new_cy, TOP);
    new_cy->bottom = init_surface(new_cy, BOTTOM);
    normalize(&new_cy->axis);
    return (new_cy);
}