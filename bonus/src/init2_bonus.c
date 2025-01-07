/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:22:43 by linyao            #+#    #+#             */
/*   Updated: 2025/01/05 11:10:24 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void    init_al(t_rt *rt, char **ss)
{
    int i;

    i = 0;
    while (ss[i])
        i++;
    if (rt->n_al)
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
    rt->n_al++;
}

void    init_cam(t_rt *rt, char **ss)
{
    int     i;
    t_cam   *cam;

    i = 0;
    while (ss[i])
        i++;
    if (i != 4)
        terminate(ERR_ARGV);
    cam = ft_calloc_new(1, sizeof(t_cam));
    if (!cam)
        terminate(ERR_MEMO);
    cam->next = NULL;
    cam->prev = NULL;
    if (rt->cam)
    {
        cam->prev = find_lstlast_cam(&(rt->cam));
        find_lstlast_cam(&(rt->cam))->next = cam;
    }
    else
        rt->cam = cam;
    init_cam_pov(ss[1], cam);
    if (ft_strlen(ss[2]) > 17)
        terminate(ERR_PARA);
    init_cam_nvec(ss[2], cam);
    init_cam_fov(ss[3], cam);
    rt->n_cam++;
}

void    init_lit(t_rt *rt, char **ss)
{
    int     i;
    t_lit   *lit;
    
    i = 0;
    while (ss[i])
        i++;
    if (i != 4)
        terminate(ERR_ARGV);
    lit = ft_calloc_new(1, sizeof(t_lit));
    if (!lit)
        terminate(ERR_MEMO);
    lit->next = NULL;
    if (rt->lit)
        find_lstlast_lit(&(rt->lit))->next = lit;
    else
        rt->lit = lit;
    init_lit_lsrc(ss[1], lit);
    check_lit_rbrt(ss[2]);
    lit->r_brt = ft_atof(ss[2]);
    if (lit->r_brt < 0 || lit->r_brt > 1)
        terminate(ERR_PARA);
    if (ft_strlen(ss[3]) > 11)
        terminate(ERR_PARA);
    init_lit_color(ss[3], lit);
    rt->n_lit++;
}

void    init_cb_scale(char *s, t_pl *pl)
{
    int i;

    if(ft_strlen(s) == 1 && !ft_isdigit(s[0]))
        terminate("incorrect tile scale..\n");
    check_point(s);
    check_extreme(s);
    i = -1;
    while (s[++i])
        if (!ft_isdigit(s[i]) && s[i] != '.')
            terminate("incorrect tile scale..\n");
    pl->tile_scale = ft_atof(s);
}