/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:23:09 by linyao            #+#    #+#             */
/*   Updated: 2024/12/20 16:23:12 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vec3  set_coord(float x, float y, float z)
{
    t_vec3  new;

    new.x = x;
    new.y = y;
    new.z = z;
    return (new);
}