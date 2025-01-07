/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:56:22 by linyao            #+#    #+#             */
/*   Updated: 2025/01/06 16:50:42 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

void handle_img(t_rt *rt, t_obj *o)
{
    if (o->has_bump && !o->bump.img)
    {
        o->bump.img = mlx_xpm_file_to_image(&rt->frm, \
            o->bump.path, &o->bump.width, &o->bump.height);
        if (!o->bump.img)
            o->has_bump = false;
        else
            o->bump.buffer = mlx_get_data_addr(o->bump.img, \
                &o->bump.bitpixel, &o->bump.linesize, &o->bump.endian);
    }
    if (o->has_texture && !o->texture.img)
    {
        o->texture.img = mlx_xpm_file_to_image(&rt->frm, \
            o->texture.path, &o->texture.width, &o->texture.height);
        if (!o->texture.img)
            o->has_texture = false;
        else
            o->texture.buffer = mlx_get_data_addr(o->texture.img, \
                &o->texture.bitpixel, &o->texture.linesize, &o->texture.endian);
    }
}

void set_local_coord(t_rt *rt, t_obj *o)
{
    t_pl *pl;
    t_cy *cy;
    t_cn *cn;

    o->ly = (t_vec3)init_point(0, 1, 0);
    if (!ft_strcmp(o->typ, "pl"))
    {
        pl = (t_pl *)(o->elm);
        o->ly = pl->normal;
    }
    if (!ft_strcmp(o->typ, "cy"))
    {
        cy = (t_cy *)(o->elm);
        o->ly = cy->axis;
    }
    if (!ft_strcmp(o->typ, "cn"))
    {
        cn = (t_cn *)(o->elm);
        o->ly = cn->axis;
    }
    o->lx = vec3_cross(o->ly, rt->cam->n_vec);
    o->lz = vec3_cross(o->lx, o->ly);
    normalize(&o->lx);
    normalize(&o->ly);
    normalize(&o->lz);
}

void create_obj_norm(t_rt *rt)
{
    t_obj *o;

    rt->bitmap.addr_incr = rt->bitmap.bitpixel / 8;
    o = rt->obj;
    while (o)
    {
        if (!ft_strcmp(o->typ, "sp"))
        {
            handle_img(rt, o);
            set_local_coord(rt, o);
        }
        o = o->next;
    }
}

void bump_on_sp(t_intersect *i, t_bitmap *bm, int grey_scale[3][2])
{
    char *res;
    float uv[2];

    calculate_uv_sp(i->shape, i_pos(i), uv);
    grey_scale[0][0] = (((int)((1 - uv[0]) * bm->width)) + bm->width / 2) % bm->width;
    grey_scale[1][0] = (int)((1 - uv[1]) * bm->height);
    grey_scale[0][1] = (grey_scale[0][0] + 1) % bm->width;
    grey_scale[1][1] = (grey_scale[1][0] + 1) % bm->height;
    res = bm->buffer + \
    (grey_scale[1][0] * bm->linesize + grey_scale[0][0] * (bm->bitpixel / 8));
    grey_scale[2][0] = *((unsigned int *)res) & 0xff;
    res = bm->buffer + \
    (grey_scale[1][0] * bm->linesize + grey_scale[0][1] * (bm->bitpixel / 8));
    grey_scale[2][1] = *((unsigned int *)res) & 0xff;
    uv[0] = -((float)(grey_scale[2][0] - grey_scale[2][1])) / 10;
    res = bm->buffer + \
    (grey_scale[1][1] * bm->linesize + grey_scale[0][0] * (bm->bitpixel / 8));
    grey_scale[2][1] = *((unsigned int *)res) & 0xff;
    uv[1] = -((float)(grey_scale[2][0] - grey_scale[2][1])) / 10;
    i->nor = pertub_bump_nor(i->shape, i->nor, uv[0], uv[1]);
}

void apply_bump(t_intersect *i)
{
    int grey_scale[3][2];

    if (!i->shape->has_bump)
        return ;
    if (!ft_strcmp(i->shape->typ, "sp"))
        bump_on_sp(i, &i->shape->bump, grey_scale);
}