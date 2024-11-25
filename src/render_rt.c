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
    clock_t t;
    
    mlx_put_image_to_window(rt->frm.mlx, rt->frm.win, rt->bitmap.img, 0, 0);
    t = clock() - t;
    return (0);
}