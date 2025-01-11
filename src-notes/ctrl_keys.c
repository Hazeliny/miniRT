/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:23 by linyao            #+#    #+#             */
/*   Updated: 2024/12/25 15:02:28 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	press_key(int key, void *para)
{
    t_rt	*rt;

	ft_printf("%d Test\n", key);
	rt = (t_rt *)para;
    if (key == KEY_ESC || key == KEY_Q)
        exit_program(rt);
    else if (key == KEY_LEFT)
    {
        rt->cam = rt->cam->prev;
        mlx_put_image_to_window(rt->frm.mlx, rt->frm.win, \
                        rt->cam->bm->img, 0, 0);
    }
    else if (key == KEY_RIGHT)
    {
        rt->cam = rt->cam->next;
        mlx_put_image_to_window(rt->frm.mlx, rt->frm.win, \
                        rt->cam->bm->img, 0, 0);
    }
/*
    else if (key == KEY_W)
        rt->cam->pov.y += 5;
    else if (key == KEY_S)
        rt->cam->pov.y -= 5;
    else if (key == KEY_A)
        rt->cam->pov.x -= 5;
    else if (key == KEY_D)
        rt->cam->pov.x += 5;
    else if (key == KEY_C)
        rt->cam->pov.z += 5;
    else if (key == KEY_V)
        rt->cam->pov.z -= 5;
*/
//    render_rt(rt);
    return (0);
}

int press_mouse(int mouse, int x, int y, t_rt *rt)
{
    if (mouse == 1)
    {
        rt->event.btn_l = 1;
        x = x - rt->frm.axis_x / 2;
        y = rt->frm.axis_y / 2 - y;
        rt->coord = set_coord(0, x, y);
    }
    return (0);
}

int release_mouse(int mouse, int x, int y, t_rt *rt)
{
    if (mouse == 1 && x > 0 && y > 0)
    {
        if (rt->event.key_ctrl)
            render_rt(rt);
    }
    return (0);
}