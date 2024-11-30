/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:02:02 by linyao            #+#    #+#             */
/*   Updated: 2024/11/30 18:03:52 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_obj   init_surface(t_cy *cy, int surface)
{
    t_obj   new;
    t_pl    pl;

    pl.p = cy->center;
    if (surface)
        pl.normal = vec3_mpl(cy->axis, -1);
    else
    {
        pl.p = vec3_sum(vec3_mpl(cy->axis, cy->hgt), cy->center);
        pl.normal = cy->axis;
    }
    pl.rgb = cy->rgb;
    new.elm = &pl;
    ft_strlcpy(new.typ, "pl", 3);
    new.vtable->is_intersect = &pl_intersect;
    new.vtable->update_inter = &pl_update_inter;
    return (new);
}

int cy_intersect(t_intersect *i, void *elm, int f)
{
    
}

void cy_update_inter(t_intersect *i, void *elm)
{
    
}

t_vec3  get_cynormal(t_cy *cy, t_vec3 pos)
{
    t_vec3  vec;
    t_vec3  proj;
    float   proj_len;

    vec = vec3_sub(&pos, &cy->center);
    proj_len = vec3_dot(&cy->axis, &vec);
    proj = vec3_mpl(cy->axis, proj_len);
    vec = vec3_sub(&vec, &proj);
    normalize(&vec);
    return (vec);
}