/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 22:55:57 by linyao            #+#    #+#             */
/*   Updated: 2025/01/08 00:24:37 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"
/*
t_vec3 compute_half_vector(t_intersect *i, t_view *view)
{
    t_vec3 h = vec3_sum(i->ray.direction, view->forward);
    normalize(&h);
    return (h);
}
*/
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

//float d = ggx_distribution(hit->nhit, half_vector, obj->roughness);
/*/////////
float smithG1(float NdotX, float alpha)
{
    if (NdotX <= 0.0f)
        return 0.0f;

    float alpha2 = sqr(alpha);
    float NdotX2 = sqr(NdotX);
    float denom = NdotX + sqrtf(alpha2 + (1.0f - alpha2) * NdotX2);
    return (2.0f * NdotX / denom);
}
*//////////////////
/*//////////////////
float smithGeometry(float NdotV, float NdotL, float alpha)
{
    return (smithG1(NdotV, alpha) * smithG1(NdotL, alpha));
}
*//////////////////////

float compute_smith_geometry(t_intersect *i, float roughness)// roughness is from obj->texture_f
{
    t_vec3  N = i->nor;
    t_vec3  L = i->ray.direction;
    t_vec3  V = vec3_mpl(L, -1);
    float   NdotV = vec3_dot(&N, &V);
    float   NdotL = vec3_dot(&N, &L);
    float   k = (roughness + 1.0) * (roughness + 1.0) / 8.0;
    float   g1_v = NdotV / (NdotV * (1.0 - k) + k);
    float   g1_l = NdotL / (NdotL * (1.0 - k) + k);
    return (g1_v * g1_l);
//    return (smithG1(NdotV, sqr(roughness)) * smithG1(NdotL, sqr(roughness)));
//    return (smithGeometry(NdotV, NdotL, sqr(roughness)));
}

float compute_fresnel(t_intersect *i, float f0)
{
    float cos_theta = vec3_dot(&i->ray.direction, &i->nor);
    
    // 确保cos_theta在[0, 1]范围内，避免数值错误
    if (cos_theta < 0.0f)
        cos_theta = 0.0f;  // 如果是内射光，取0
    // 使用Schlick近似公式计算菲涅尔反射率
    return (f0 + (1.0f - f0) * powf(1.0f - cos_theta, 5.0f));
//    return fresnel_schlick(cos_theta, F0);
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
    h = vec3_sum(v, l);
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