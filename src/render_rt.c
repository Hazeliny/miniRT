/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:44:08 by linyao            #+#    #+#             */
/*   Updated: 2024/11/27 22:48:19 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int render_rt(t_rt *rt)
{
    clock_t time;
    float   x;
    float   y;
    t_intersect i;
    t_view   view;

    view = create_view(rt->cam);
    y = 0;
    while (y < WINY)
    {
        x = 0;
        while (x < WINX)
        {
            i.t = T_VALUE_MAX;
            i.ray = create_ray(&view, planarize((x * 2) / (float)WINX - 1, (y * 2) / (float)WINY - 1));
{
            x++;
        }
        y++;
    }
    
    
    mlx_put_image_to_window(rt->frm.mlx, rt->frm.win, rt->bitmap.img, 0, 0);
    time = clock() - time;
    return (0);
}