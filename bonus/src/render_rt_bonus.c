/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rt_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:44:08 by linyao            #+#    #+#             */
/*   Updated: 2025/01/08 00:23:38 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void    write_pixel(t_bitmap *bm, int color, int x, int y)
{
    char    *s;

    s = bm->buffer + (y * bm->linesize + x * (bm->bitpixel / 8));
    *(unsigned int *)s = color;
}

void    ray_trace(t_rt *rt, t_cam *cam)
{
    float   x;
    float   y;
    t_intersect i;
    t_view   view;

    view = create_view(cam);
    y = 0;
    while (y < WINY)
    {
        x = 0;
        while (x < WINX)
        {
            i.t = T_VALUE_MAX;
            i.ray = create_ray(&view, planarize((x * 2) / (float)WINX - 1, \
                (y * 2) / (float)WINY - 1));
            if (obj_intersect(&i, &(rt->obj)))
                write_pixel(cam->bm, \
                    rgb_toi(color_intersect(rt, &i, i.shape)), x, y);
            x++;
        }
        y++;
    }
}

t_bitmap    *create_bitmap(t_mlx *frm)
{
    t_bitmap    *bm;

    bm = ft_calloc_new(1, sizeof(t_bitmap));
    if (!bm)
        terminate(ERR_MEMO);
    bm->img = mlx_new_image(frm->mlx, WINX, WINY);
    bm->buffer = mlx_get_data_addr(bm->img, &bm->bitpixel, \
        &bm->linesize, &bm->endian);
    return (bm);
}

void    render(t_rt *rt)
{
    t_cam   *cam;
    bool    is_first_cam;

    is_first_cam = true;
    cam = rt->cam;
    while (cam)
    {
        cam->bm = create_bitmap(&(rt->frm));
        create_obj_norm(rt);
        ray_trace(rt, cam);
        if (is_first_cam)
        {
            mlx_put_image_to_window(rt->frm.mlx, rt->frm.win, \
                                cam->bm->img, 0, 0);
            is_first_cam = false;
        }
        cam = cam->next;
    }
    rt->cam->prev = find_lstlast_cam(&(rt->cam));
    (find_lstlast_cam(&(rt->cam)))->next = rt->cam;
    rt->bitmap = *(rt->cam->bm);
}

int render_rt(t_rt *rt)
{
    clock_t time;

    time = clock();
    render(rt);
    time = clock() - time;
    printf("save img:\t%fs\n", ((double)time) / CLOCKS_PER_SEC);
    return (0);
}