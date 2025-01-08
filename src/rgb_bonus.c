/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:00:56 by linyao            #+#    #+#             */
/*   Updated: 2025/01/08 23:41:00 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

int rgb_toi(t_rgb rgb)
{
    int res;

    res = 00 << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b;
    return (res);
}

//to combine two colors, clamping the results to the maximum RGB value of 255
t_rgb   sum_color(t_rgb rgb1, t_rgb rgb2)
{
    t_rgb   res;

    res.r = rgb1.r + rgb2.r;
    if (res.r > 255)
        res.r = 255;
    res.g = rgb1.g + rgb2.g;
    if (res.g > 255)
        res.g = 255;
    res.b = rgb1.b + rgb2.b;
    if (res.b > 255)
        res.b = 255;
    return (res);
}

//to multiplie two RGB colors component-wise
t_rgb   mpl_color(t_rgb rgb1, t_rgb rgb2)
{
    t_rgb   res;

    res.r = ((float)rgb1.r / 255) * ((float)rgb2.r / 255) * 255;
    res.g = ((float)rgb1.g / 255) * ((float)rgb2.g / 255) * 255;
    res.b = ((float)rgb1.b / 255) * ((float)rgb2.b / 255) * 255;
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

t_rgb   rgb_color(int rgb)
{
    t_rgb   c;
    
    c.r = (float)((rgb >> 16) & 0xff) / 255;
    c.g = (float)((rgb >> 8) & 0xff) / 255;
    c.b = (float)(rgb & 0xff) / 255;
    return (c);
}