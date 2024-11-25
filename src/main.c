/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:58:41 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/25 23:48:00 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void    init_rt(t_rt *rt)
{
    rt->frm.mlx = mlx_init();
    rt->frm.win = mlx_new_window(rt->frm.mlx, WINX, WINY, "Fantastic miniRT");
    if (!rt->frm.win)
        terminate(ERR_MEMO);
    init_vtable(&(rt->obj));
    rt->bitmap.img = mlx_new_image(rt->frm.mlx, WINX, WINY);
    rt->bitmap.buffer = mlx_get_data_addr(rt->bitmap.img, \
        &rt->bitmap.bitpixel, &rt->bitmap.linesize, &rt->bitmap.endian);
}

int exit_program(void *para)
{
    t_rt    *rt;

    rt = (t_rt *)para;
    mlx_destroy_window(rt->frm.mlx, rt->frm.win);
//    free(rt->frm);
//    free(rt);
    exit (0);
}

void    control_mlx(t_rt *rt)
{
    mlx_hook(rt->frm.win, 2, 1L << 0, &press_key, rt);
//  mlx_hook(rt->frm.win, 3, 1L << 1, &release_key, rt);
//	mlx_hook(rt->frm.win, 4, 1L << 2, &press_mouse, rt);
//	mlx_hook(rt->frm.win, 5, 1L << 3, &release_mouse, rt);
//	mlx_hook(rt->frm.win, 6, 1L << 13, &move_mouse, rt);
    mlx_hook(rt->frm.win, 17, 0, &exit_program, rt);
}

int main(int ac, char **av)
{
    (void)av;
    t_rt    rt;

    if (ac == 2)
    {
        init_metadata(&rt);
        init_intersect();
        init_objs();
        // parse file here
        init_rt(&rt);
        if (render_rt(&rt) != 0)
            terminate(ERR_RENDER);
        control_mlx(&rt);
        mlx_loop(rt.frm.mlx);
        // free series of memories
    }
    else
        terminate(ERR_ARGV);
    return (0);
}
