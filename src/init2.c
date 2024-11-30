/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:22:43 by linyao            #+#    #+#             */
/*   Updated: 2024/11/30 21:56:20 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void    init_al(t_rt *rt, char **ss)
{
    int i;

    i = 0;
    while (ss[i])
        i++;
    if (&(rt->al))
        terminate(ERR_AL);
    if (i != 3)
        terminate(ERR_ARGV);
    check_al_ratio(ss[1]);
    rt->al.ratio = ft_atof(ss[1]);
    if (rt->al.ratio < 0 || rt->al.ratio > 1)
        terminate(ERR_PARA);
    if (ft_strlen(ss[2]) > 11 || init_al_rgb(ss[2], &rt->al) != 0)
        terminate(ERR_PARA);
    rt->al.color = density(&rt->al.color, rt->al.ratio);
}

void    init_cam(t_rt *rt, char **ss)
{
    int i;

    i = 0;
    while (ss[i])
        i++;
    if (i != 4)
        terminate(ERR_ARGV);
    init_cam_pov(ss[1], &rt->cam);
    if (ft_strlen(ss[2]) > 11)
        terminate(ERR_PARA);
    init_cam_nvec(ss[2], &rt->cam);
    init_cam_fov(ss[2], &rt->cam);
}

void    init_lit(t_rt *rt, char **ss)
{
    int i;
    
    i = 0;
    while (ss[i])
        i++;
    if (i != 4)
        terminate(ERR_ARGV);
    init_lit_lsrc(ss[1], &rt->lit);
    check_lit_rbrt(ss[2]);
    rt->lit.r_brt = ft_atof(ss[2]);
    if (rt->lit.r_brt < 0 || rt->lit.r_brt > 1)
        terminate(ERR_PARA);
    if (ft_strlen(ss[3]) > 11)
        terminate(ERR_PARA);
    init_lit_color(ss[3], &rt->lit);
}