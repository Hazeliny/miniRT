/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:15:23 by linyao            #+#    #+#             */
/*   Updated: 2024/12/01 22:03:07 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	press_key(int key, void *para)
{
    t_rt	*rt;

	ft_printf("%d Test\n", key);
	rt = (t_rt *)para;
    if (key == ESC || key == Q)
        exit_program(rt);
    else if (key == W)
        rt->cam.pov.y += 5;
    else if (key == S)
        rt->cam.pov.y -= 5;
    else if (key == A)
        rt->cam.pov.x -= 5;
    else if (key == D)
        rt->cam.pov.x += 5;
    else if (key == C)
        rt->cam.pov.z += 5;
    else if (key == V)
        rt->cam.pov.z -= 5;
    render_rt(rt);
    return (0);
}
