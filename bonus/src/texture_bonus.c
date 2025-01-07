/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:40:15 by linyao            #+#    #+#             */
/*   Updated: 2025/01/07 13:40:18 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT_bonus.h"

t_vec3 compute_half_vector(t_intersect *i, t_rt *rt)
{
    t_vec3 h = vec3_sum(i->ray.direction, rt->cam->n_vec);
    normalize(&h);
    return (h);
}

float ggx_distribution(t_vec3 *nor, t_vec3 *h, float roughness)
{
    float nh;
    float alpha;
    float denom;

	nh = vec3_dot(nor, h);
    alpha = roughness * roughness;
    denom = nh * nh * (alpha - 1.0) + 1.0;
    return (alpha / (M_PI * denom * denom));
}

//float d = ggx_distribution(hit->nhit, half_vector, obj->roughness);

float smithG1(float NdotX, float alpha)
{
    if (NdotX <= 0.0f)
        return 0.0f;

    float alpha2 = sqr(alpha);
    float NdotX2 = sqr(NdotX);
    float denom = NdotX + sqrtf(alpha2 + (1.0f - alpha2) * NdotX2);
    return (2.0f * NdotX / denom);
}
/*
float smithGeometry(float NdotV, float NdotL, float alpha)
{
    return (smithG1(NdotV, alpha) * smithG1(NdotL, alpha));
}
*/
float computeGeometry(t_intersect *i, t_rt *rt, float roughness)// roughness is from obj->texture_f
{
    t_vec3  N = i->nor;
    t_vec3  L = i->ray.direction;
    t_vec3  V = vec3_mpl(L, -1);
    float   NdotV = vec3_dot(&N, &V);
    float   NdotL = vec3_dot(&N, &L);
    return (smithG1(NdotV, sqr(roughness)) * smithG1(NdotL, sqr(roughness)));
//    return (smithGeometry(NdotV, NdotL, sqr(roughness)));
}

float compute_fresnel(t_intersect *i, float F0)
{
    float cos_theta = vec3_dot(&i->ray.direction, &i->nor);
    
    // 确保cos_theta在[0, 1]范围内，避免数值错误
    if (cos_theta < 0.0f)
        cos_theta = 0.0f;  // 如果是内射光，取0
    // 使用Schlick近似公式计算菲涅尔反射率
    return (F0 + (1.0f - F0) * powf(1.0f - cos_theta, 5.0f));
//    return fresnel_schlick(cos_theta, F0);
}

t_rgb get_pixelcolor(t_bitmap *bm, float u, float v)
{
    int x = (int)(u * bm->width);
    int y = (int)(v * bm->height);
    t_rgb   color;
    int pixel_i;

    x = fmin(fmax(x, 0), bm->width - 1);
    y = fmin(fmax(y, 0), bm->height - 1);
    pixel_i = (y * bm->linesize) + (x * (bm->bitpixel / 8));
    if (bm->endian == 1)
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

t_vec3 calculate_tangent(t_vec3 normal)
{
    t_vec3 tangent;
    t_vec3 ref;

    if (fabs(normal.x) > 0.9)
        ref = (t_vec3){0, 1, 0};
    else
        ref = (t_vec3){1, 0, 0};
    tangent = vec3_cross(normal, ref);
    normalize(&tangent);
    return tangent;
}

t_vec3  perturb_texture_nor(t_vec3 normal, t_vec3 texture_nor)
{
    // 计算切线和副法向量
    t_vec3 tangent = calculate_tangent(normal);
    t_vec3 bitangent = vec3_cross(normal, tangent);

    // 将纹理法向量映射到世界空间
    t_vec3 perturbed_normal = vec3_sum(vec3_mpl(tangent, texture_nor.x), \
        vec3_sum(vec3_mpl(bitangent, texture_nor.y), \
            vec3_mpl(normal, texture_nor.z)));
    normalize(&perturbed_normal);
    return (perturbed_normal);
}

t_rgb texture_on_sp(t_intersect *i, t_bitmap *bm)
{
    float uv[2];
    t_vec3  normal;
    t_vec3  texture_nor;
    t_rgb   texture_rgb;
    float   dot;

    calculate_uv_sp(i->shape, i_pos(i), uv);
    texture_nor = get_normal_from_texture(&i->shape->texture, uv);
//    normal = get_spnormal((t_sp *)i->shape->elm, i_pos(i));
    i->nor = perturb_texture_nor(i->nor, texture_nor);
    texture_rgb = get_pixelcolor(&i->shape->texture, uv[0], uv[1]);

    // 进行光照计算（例如：漫反射 + 镜面反射）
//    dot = light_dot(i, lit);
//    texture_rgb = apply_light(texture_rgb, dot);  // 应用光照

    return texture_rgb;
}

void	apply_texture(t_intersect *i)
{
//    int grey_scale[3][2];

    if (!i->shape->has_texture)
        return ;
    if (!ft_strcmp(i->shape->typ, "sp"))
        texture_on_sp(i, &i->shape->texture);
}