/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:55:57 by linyao            #+#    #+#             */
/*   Updated: 2025/01/09 09:53:41 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_vec3 compute_half_vector(t_intersect *i, t_view *view)
{
    t_vec3 h = vec3_sum(i->ray.direction, view->forward);
    normalize(&h);
    return (h);
}

float ggx_distribution(t_vec3 *nor, t_vec3 *h, float roughness)
{
    float nh;
    float alpha;
    float denom;

	nh = vec3_dot(nor, h);
    if (nh <= 0.0)
        return (0.0);
    alpha = sqr(roughness);
    denom = sqr(nh) * (alpha - 1.0) + 1.0;
    return (alpha / (M_PI * sqr(denom)));
}

float compute_smith_geometry(t_intersect *i, float roughness)// roughness is from obj->texture_f
{
    t_vec3  n = i->nor;
    t_vec3  l = i->ray.direction;
    t_vec3  v = vec3_mpl(l, -1);
    float   NdotV = vec3_dot(&n, &v);
    float   NdotL = vec3_dot(&n, &l);
    float   k = sqr(roughness + 1.0) / 8.0;
    float   g1_v = NdotV / (NdotV * (1.0 - k) + k);
    float   g1_l = NdotL / (NdotL * (1.0 - k) + k);
    return (g1_v * g1_l);
}

float compute_fresnel(t_intersect *i, float f0)
{
    float cos_theta;

    cos_theta = vec3_dot(&i->ray.direction, &i->nor);
    if (cos_theta < 0.0f)
        cos_theta = 0.0f;
    return (f0 + (1.0f - f0) * powf(1.0f - cos_theta, 5.0f));
}

t_rgb   matting(t_intersect *i, t_lit *lit, t_rgb ds, t_rgb (*rgb)[2])
{
    float   rough;
    t_vec3  n;
    t_vec3  l;
    t_vec3  v;
    t_vec3  h;
    float   nv;
    float   nl;
    float   d;
    float   g;
    float   f;

    rough = i->shape->texture_f;
    n = i->nor;
    l = vec3_mpl(i->ray.direction, -1);
    v = vec3_mpl(i->ray.direction, -1);
//    v = vec3_mpl(i->shape->h, -1);
//    h = vec3_sum(v, l);
    h = i->shape->h;
    normalize(&h);
    d = ggx_distribution(&n, &h, rough);
    g = compute_smith_geometry(i, rough);
    f = compute_fresnel(i, 0.04f);
    nv = vec3_dot(&n, &v);
    nl = vec3_dot(&n, &l);
    if (nl > 0.0f && nv > 0.0f)
    {
        (*rgb)[1] = sum_color(sum_color(mpl_color(ds, (*rgb)[0]), \
        density(&lit->color, (d * g * f) / (4.0f * nv * nl))), (*rgb)[1]);
    }
    return ((*rgb)[1]);  
}