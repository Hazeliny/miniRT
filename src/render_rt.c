/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:44:08 by linyao            #+#    #+#             */
/*   Updated: 2024/11/25 16:57:37 by linyao           ###   ########.fr       */
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

            x++;
        }
        y++;
    }
    
    
    mlx_put_image_to_window(rt->frm.mlx, rt->frm.win, rt->bitmap.img, 0, 0);
    time = clock() - time;
    return (0);
}