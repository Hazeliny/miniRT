/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:44:08 by linyao            #+#    #+#             */
/*   Updated: 2024/12/18 22:25:04 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void    write_pixel(t_bitmap *bm, int color, int x, int y)
{
    char    *s;

    s = bm->buffer + (y * bm->linesize + x * (bm->bitpixel / 8));
    *(unsigned int *)s = color;
}

void    ray_trace(t_rt *rt, t_cam *cam)
{
    float   x;
    float   y;
    t_intersect i;
    t_view   view;

    view = create_view(cam);
    y = 0;
    while (y < WINY)
    {
        x = 0;
        while (x < WINX)
        {
            i.t = T_VALUE_MAX;
//Per-Pixel Ray Generation:
//For each screen pixel (x, y), a ray is generated using create_ray
            i.ray = create_ray(&view, planarize((x * 2) / (float)WINX - 1, \
                (y * 2) / (float)WINY - 1)); //planarize's transformations map screen coordinates into a normalized device coordinate (NDC) space, where the screen is represented as a 2D plane ranging from -1 to 1 along both axes.
/*            printf("i.ray origin: %f, %f, %f; direction: %f, %f, %f; t: %f\n", \
                    i.ray.origin.x, i.ray.origin.y, i.ray.origin.z, \
                    i.ray.direction.x, i.ray.direction.y, i.ray.direction.z, \
                    i.ray.t_max);///////////////////////////
*/
//Ray-Object Intersection Testing: obj_intersect iterates over the linked list of objects and checks for intersections.
//Each object's is_intersect function is called, encapsulating type-specific intersection logic.
            if (obj_intersect(&i, &(rt->obj)))
//Updating Pixel Colors: If an intersection is found: Intersection details are stored in i. The pixel's color is computed and written to the image buffer.
//Final Image: After all pixels are processed, the image buffer contains the rendered scene.
                write_pixel(cam->bm, \
                    rgb_toi(color_intersect(rt, &i, i.shape)), x, y);
            x++;
        }
        y++;
    }
}

t_bitmap    *create_bitmap(t_mlx *frm)
{
    t_bitmap    *bm;

    bm = ft_calloc_new(1, sizeof(t_bitmap));
    if (!bm)
        terminate(ERR_MEMO);
    bm->img = mlx_new_image(frm->mlx, WINX, WINY);
    bm->buffer = mlx_get_data_addr(bm->img, &bm->bitpixel, \
        &bm->linesize, &bm->endian);
    return (bm);
}

void    render(t_rt *rt)
{
    t_cam   *cam;
    bool    is_first_cam;

    is_first_cam = true;
    cam = rt->cam;
    while (cam)
    {
        cam->bm = create_bitmap(&(rt->frm));
        ray_trace(rt, cam);
        if (is_first_cam)
        {
            mlx_put_image_to_window(rt->frm.mlx, rt->frm.win, \
                                cam->bm->img, 0, 0);
            is_first_cam = false;
        }
        cam = cam->next;
    }
    rt->cam->prev = find_lstlast_cam(&(rt->cam));
    (find_lstlast_cam(&(rt->cam)))->next = rt->cam;
    rt->bitmap = *(rt->cam->bm);
}

int render_rt(t_rt *rt)
{
    clock_t time;

    time = clock();
    render(rt);
//    ray_trace(rt);
//    mlx_put_image_to_window(rt->frm.mlx, rt->frm.win, rt->bitmap.img, 0, 0);
    time = clock() - time;
    printf("save img:\t%fs\n", ((double)time) / CLOCKS_PER_SEC);
    return (0);
}

/*
Advantages of This Design
Polymorphism with vtable: Each object type has its own specific intersection logic encapsulated in the vtable, making it easy to extend support for new object types (e.g., cones).
Modular and Maintainable: The main ray tracing loop (ray_trace) is clean and does not need to know type-specific details.
Efficient Intersection Handling:
By using vtable, there's no need for cumbersome if-else or switch statements for type checking.
Scalability: Adding new object types is straightforward. Define the intersection and update logic, initialize the vtable, and integrate it into the pipeline.
This modular design is a hallmark of a well-structured ray tracer.
*/