/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:44:08 by linyao            #+#    #+#             */
/*   Updated: 2024/11/29 16:12:28 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void    write_pixel(t_bitmap *bm, int color, int x, int y)
{
    char    *s;

    s = bm->img + (y * bm->linesize + x * (bm->bitpixel / 8));
    *(unsigned int *)s = color;
}

void    ray_trace(t_rt *rt)
{
    float   x;
    float   y;
    t_intersect i;
    t_view   view;

    view = create_view(&rt->cam);
    y = 0;
    while (y < WINY)
    {
        x = 0;
        while (x < WINX)
        {
            i.t = T_VALUE_MAX;
            i.ray = create_ray(&view, planarize((x * 2) \
                    / (float)WINX - 1, (y * 2) / (float)WINY - 1));
            if (obj_intersect(i, &(rt->obj)))
                write_pixel(rt->cam.bm, x, y, rgb_toi(color_intersect(rt, &i, i.shape)));
            x++;
        }
        y++;
    }
}

int render_rt(t_rt *rt)
{
    clock_t time;

    time = clock();
    ray_trace(rt);
    mlx_put_image_to_window(rt->frm.mlx, rt->frm.win, rt->bitmap.img, 0, 0);
    time = clock() - time;
    printf("save img:\t%fs\n", ((double)time) / CLOCKS_PER_SEC);
    return (0);
}