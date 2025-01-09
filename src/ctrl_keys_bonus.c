/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_keys_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:23 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 18:52:04 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

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
	return (0);
}

int	press_mouse(int mouse, int x, int y, t_rt *rt)
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

int	release_mouse(int mouse, int x, int y, t_rt *rt)
{
	if (mouse == 1 && x > 0 && y > 0)
	{
		if (rt->event.key_ctrl)
			render_rt(rt);
	}
	return (0);
}
