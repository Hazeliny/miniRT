/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:59:44 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 00:20:14 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_rgb get_pixelcolor(t_bitmap *bm, float u, float v)
{
    int x = (int)(u * bm->width);
    int y = (int)(v * bm->height);
    t_rgb   color;
    int pixel_i;

    x = fmin(fmax(x, 0), bm->width - 1);
    y = fmin(fmax(y, 0), bm->height - 1);
    pixel_i = (y * bm->linesize) + (x * (bm->bitpixel / 8));
    if (bm->endian == 0)
    {
        color.r = (unsigned char)bm->buffer[pixel_i + 2];
        color.g = (unsigned char)bm->buffer[pixel_i + 1];
        color.b = (unsigned char)bm->buffer[pixel_i];
    }
    else
    {
        color.r = (unsigned char)bm->buffer[pixel_i];
        color.g = (unsigned char)bm->buffer[pixel_i + 1];
        color.b = (unsigned char)bm->buffer[pixel_i + 2];
    }
    return (color);
}

t_vec3  get_normal_from_texture(t_bitmap *bm, float uv[2])
{
    t_rgb   color;
    t_vec3  normal;

    color = get_pixelcolor(bm, uv[0], uv[1]);
    normal.x = (color.r / 255.0f) * 2.0f - 1.0f;
    normal.y = (color.g / 255.0f) * 2.0f - 1.0f;
    normal.z = (color.b / 255.0f) * 2.0f - 1.0f;
    normalize(&normal);
    return (normal);
}