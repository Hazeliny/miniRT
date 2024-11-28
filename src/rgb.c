/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:00:56 by linyao            #+#    #+#             */
/*   Updated: 2024/11/28 16:00:59 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_rgb   sum_color(t_rgb *rgb1, t_rgb *rgb2)
{
    t_rgb   res;

    res.r = rgb1->r + rgb2->r;
    if (res.r > 255)
        res.r = 255;
    res.g = rgb1->g + rgb2->g;
    if (res.g > 255)
        res.g = 255;
    res.b = rgb1->b + rgb2->b;
    if (res.b > 255)
        res.b = 255;
    return (res);
}

t_rgb   density(t_rgb *rgb, float dense)
{
    t_rgb   res;

    res.r = rgb->r * dense;
    res.g = rgb->g * dense;
    res.b = rgb->b * dense;
    return (res);
}