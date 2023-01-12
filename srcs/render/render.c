/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:32:56 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/12 15:28:53 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*offset;

	offset = data->addr + (y * data->line_length + x * (data->bpp >> 3));
	*(unsigned int *)offset = color;
}

t_ray	build_camera_ray(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_vec3	pixel_raster;
	t_vec3	pixel_ndc;
	t_vec3	pixel_screenspace;
	t_vec3	pixel_camera;

	pixel_raster.x = (float)x + 0.5f;
	pixel_raster.y = (float)y + 0.5f;
	pixel_ndc.x = pixel_raster.x / (float)scene->win_w;
	pixel_ndc.y = pixel_raster.y / (float)scene->win_h;
	pixel_screenspace.x = 2.0f * pixel_ndc.x - 1.0f;
	pixel_screenspace.y = 1.0f - (2.0f * pixel_ndc.y);
	pixel_camera.x = pixel_screenspace.x * scene->image_ratio * \
			scene->cam.fov_h_len;
	pixel_camera.y = pixel_screenspace.y * scene->cam.fov_h_len;
	pixel_camera.z = -1;
	ray.origin = scene->cam.pos;
	ray.dir = vec_sub(pixel_camera, ray.origin);
	ray.dir = vec_normalize(ray.dir);
	return (ray);
}

int	find_closest_obj(t_scene *scene, t_ray ray, t_func *inter, float *hit_dist)
{
	int		k;
	int		closest_obj;
	float	closest_distance;

	k = -1;
	closest_obj = -1;
	closest_distance = INFINITY;
	while (++k < scene->num_objects_in_scene)
	{
		if ((*inter)[scene->objtab[k]->objtp](ray, scene->objtab[k], hit_dist))
		{
			if (closest_distance > *hit_dist)
			{
				closest_distance = *hit_dist;
				closest_obj = k;
			}
		}
	}
	return (closest_obj);
}

int	compute_pixel(t_scene *s, int i, int j, t_func *inter)
{
	t_ray			ray;
	int				closest_obj;
	int				hit_color;
	t_surfaceinfo	info;

	info.hit_dist = 0;
	closest_obj = -1;
	ray = build_camera_ray(s, i, j);
	closest_obj = find_closest_obj(s, ray, inter, &info.hit_dist);
	if (closest_obj != -1)
	{
		get_surfaceinfo(&info, s->objtab[closest_obj], ray);
		if (s->objtab[closest_obj]->objtp == 0 \
		|| s->objtab[closest_obj]->objtp == 2)
		{
			hit_color = lambert(s, info, closest_obj, inter);
			my_mlx_pixel_put(s->ig, i, j, hit_color);
		}
		else
			my_mlx_pixel_put(s->ig, i, j, s->objtab[closest_obj]->metacolor);
	}
	else
		my_mlx_pixel_put(s->ig, i, j, s->bg_color);
	return (closest_obj);
}

int	render(t_scene *scene, t_func *inter)
{
	int	i;
	int	j;

	j = -1;
	while (++j < scene->win_h)
	{
		i = -1;
		while (++i < scene->win_w)
		{
			compute_pixel(scene, i, j, inter);
		}
	}
	return (0);
}
