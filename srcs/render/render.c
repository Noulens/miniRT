/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:32:56 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/11 17:19:44 by hyunah           ###   ########.fr       */
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
	// when camera is moving, has to do these calculations.
	// matrix_transformation(); one for ray.origin
	// matrix_transformation(); other for ray.dir
	ray.dir = vec_sub(pixel_camera, ray.origin);
	ray.dir = vec_normalize(ray.dir);
	// printf("raydir(%i)(%i): (%f %f %f)\n", x, y, ray.dir.x, ray.dir.y, ray.dir.z);
	return (ray);
}

t_surfaceinfo	get_surfaceinfo_sphere(t_stdobj *obj, t_ray ray, float hit_dist)
{
	t_surfaceinfo	info;
	t_sp		*sphere;

	sphere = (t_sp *)obj->obj;
	info.hit_dist = hit_dist;
	info.hit_point = vec_add(ray.origin, vec_scale(ray.dir, hit_dist));
	info.hit_normal = vec_normalize(vec_sub(info.hit_point, sphere->pos));
	info.view_dir = vec_normalize(vec_scale(ray.dir, -1));
	return (info);
}

t_surfaceinfo	get_surfaceinfo(t_stdobj *obj, t_ray ray, float hit_dist)
{
	t_surfaceinfo	info;

	if (obj->objtp == 0)
		info = get_surfaceinfo_sphere(obj, ray, hit_dist);
	return (info);
}

float	ft_max(float a, float b)
{
	if (a <= b)
		return (b);
	return (a);
}

int	compute_pixel(t_scene *scene, int i, int j, t_func *inter)
{
	t_ray	ray;
	int		k;
	int		closest_obj;
	float	facing_ratio;
	float	closest_distance;
	int		hit_color;
	int		r;
	int		g;
	int		b;
	float	hit_dist;
	t_surfaceinfo	info;

	k = -1;
	closest_obj = -1;
	closest_distance = INFINITY;
	while (++k < scene->num_objects_in_scene)
	{
		ray = build_camera_ray(scene, i, j);
		if ((*inter)[scene->objtab[k]->objtp](ray, scene->objtab[k], &hit_dist))
		{
			if (closest_distance > hit_dist)
			{
				closest_distance = hit_dist;
				closest_obj = k;
			}
		}
	}
	if (closest_obj != -1)
	{
		info = get_surfaceinfo(scene->objtab[closest_obj], ray, hit_dist);
		if (scene->objtab[closest_obj]->objtp == 0)
		{
			facing_ratio = ft_max(0.0f, vec_dot(info.hit_normal, info.view_dir));
			r = get_r(scene->objtab[closest_obj]->metacolor) * facing_ratio;
			g = get_g(scene->objtab[closest_obj]->metacolor) * facing_ratio;
			b = get_b(scene->objtab[closest_obj]->metacolor) * facing_ratio;
			hit_color = ft_trgb(255, r, g, b);
			my_mlx_pixel_put(scene->ig, i, j, hit_color);
		}
		else
			my_mlx_pixel_put(scene->ig, i, j, scene->objtab[closest_obj]->metacolor);
	}
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
