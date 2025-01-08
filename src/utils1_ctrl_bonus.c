/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_ctrl_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:23:09 by linyao            #+#    #+#             */
/*   Updated: 2024/12/27 12:30:25 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_vec3  set_coord(float x, float y, float z)
{
    t_vec3  new;

    new.x = x;
    new.y = y;
    new.z = z;
    return (new);
}