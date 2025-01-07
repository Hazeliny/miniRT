/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:58:41 by linyao            #+#    #+#             */
/*   Updated: 2025/01/06 12:04:49 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void    init_event(t_rt *rt)
{
    rt->event.key_ctrl = 0;
    rt->event.key_shift = 0;
	rt->event.btn_l = 0;
	rt->event.btn_m = 0;
	rt->event.btn_r = 0;
}

void    init_rt(t_rt *rt)
{
    rt->frm.mlx = mlx_init();
    rt->frm.win = mlx_new_window(rt->frm.mlx, WINX, WINY, "miniRT");
    if (!rt->frm.win)
        terminate(ERR_MEMO);
    rt->frm.axis_x = WINX;
    rt->frm.axis_y = WINY;
    rt->obj = NULL;
    rt->cam = NULL;
    rt->lit = NULL;
    rt->n_al = 0;
    rt->n_cam = 0;
    rt->n_lit = 0;
    init_event(rt);
}

int exit_program(void *para)
{
    t_rt    *rt;

    rt = (t_rt *)para;
    mlx_clear_window(rt->frm.mlx, rt->frm.win);
    if (rt->frm.win)
        mlx_destroy_window(rt->frm.mlx, rt->frm.win);
    if (rt->bitmap.img)
        mlx_destroy_image(rt->frm.mlx, rt->bitmap.img);
    if (rt->frm.mlx)
        free(rt->frm.mlx);
    rt->frm.mlx = NULL;
    free_rt(rt);
    exit (0);
}

void    control_mlx(t_rt *rt)
{
    mlx_hook(rt->frm.win, 2, 1L << 0, &press_key, rt);
//    mlx_hook(rt->frm.win, 3, 1L << 1, &release_key, rt);
//  	mlx_hook(rt->frm.win, 4, 1L << 2, &press_mouse, rt);
//  	mlx_hook(rt->frm.win, 5, 1L << 3, &release_mouse, rt);
//  	mlx_hook(rt->frm.win, 6, 1L << 13, &move_mouse, rt);
    mlx_hook(rt->frm.win, 17, 0, &exit_program, rt);
}

int main(int ac, char **av)
{
    t_rt    rt;

    if (ac == 2)
    {
        init_rt(&rt);
        parse(&rt, av[1]);
        if (render_rt(&rt) != 0)
            terminate(ERR_RENDER);
        control_mlx(&rt);
        mlx_loop(rt.frm.mlx);
        free_rt(&rt);
    }
    else
        terminate(ERR_ARGV);
    return (0);
}
