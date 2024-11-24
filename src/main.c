/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:58:41 by mpietrza          #+#    #+#             */
/*   Updated: 2024/11/24 22:44:27 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../lib/libft/libft.h"
#include "../minilibx_macos/mlx.h"

void    init_rt(t_rt *rt)
{
//    rt->frm = ft_calloc(sizeof(t_mlx), 1);
//    if (!rt->frm)
//        terminate(ERR_MEMO);
    rt->frm.mlx = mlx_init();
    rt->frm.win = mlx_new_window(rt->frm.mlx, WINX, WINY, "Fantastic miniRT");
    if (!rt->frm.win)
        terminate(ERR_MEMO);
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
    mlx_hook(rt->frm.win, 17, 0, &exit_program, rt);
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
//    t_rt    *rt;
    t_rt    rt;

//    rt = ft_calloc(sizeof(t_rt), 1);
//    if (!rt)
//        terminate(ERR_MEMO);
    init_rt(&rt);
    control_mlx(&rt);
    mlx_loop(rt.frm.mlx);
    return (0);
}
