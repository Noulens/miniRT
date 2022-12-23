/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:32:56 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/23 17:18:32 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*offset;

	offset = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)offset = color;
}

t_ray	build_camera_ray(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_vec3	pixel_raster;
	t_vec3	pixel_ndc;
	t_vec3	pixel_screenspace;
	t_vec3	pixel_camera;

	pixel_raster.x = x + 0.5;
	pixel_raster.y = y + 0.5;
	pixel_ndc.x = pixel_raster.x / scene->win_w;
	pixel_ndc.y = pixel_raster.y / scene->win_h;
	pixel_screenspace.x = 2.0 * pixel_ndc.x - 1.0;
	pixel_screenspace.y = 1.0 - (2.0 * pixel_ndc.y);
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

void	ft_swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	intersect(t_ray ray, t_scene *scene)
{
	float	t0;
	float	t1;
	float	tca;
	float	thc;
	float	d2;
	float	sphere_radius;
	t_vec3	sphere_pos;
	t_vec3	l;

	//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
	////////varaibles to be replaced from parsing.///////
	(void) scene;
	sphere_radius = 0.2;
	sphere_pos = set_vec(0, 0, -1);
	////////////////////////////////////////////////////

	l = vec_sub(sphere_pos, ray.origin);
	tca = vec_dot(l, ray.dir);
	if (tca < 0)
		return (0);
	d2 = vec_dot(l, l) - tca * tca;
	if (d2 > sphere_radius)
		return (0);
	thc = sqrt(sphere_radius - d2);
	t0 = tca - thc;
	t1 = tca + thc;
	if (t0 > t1)
		ft_swap(&t0, &t1);
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (0);
	}
	return (1);
}

void	compute_pixel(t_img *img, int i, int j)
{
	t_ray	ray;

	ray = build_camera_ray(img->scene, i, j);
	if (intersect(ray, img->scene))
	{
		// do complex shading here but for now basic (just constant color)
		my_mlx_pixel_put(img, i, j, ft_trgb(255, 255, 0, 0));
	}
	else
		my_mlx_pixel_put(img, i, j, img->scene->bg_color);
	// when we have several objects, we need to iteracte throu all objects.
	// int		k;
	// k = -1;
	// while (++k < scene->num_objects_in_scene)
	// {
		// ray = build_camera_ray(i, j);
		// if (intersect(ray, scene))
		// {
			// do complex shading here but for now basic (just constant color)
			// framebuffer[j * scene->win_w + i] = scene->objects[k].color;
		// }
		// else
		// {
			// or don't do anything and leave it black
			// framebuffer[j * scene->win_w + i] = scene->bg_color;
		// }
	// }
}

int	render(t_img *img)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++j < img->scene->win_h)
	{
		i = -1;
		while (++i < img->scene->win_w)
		{
			compute_pixel(img, i, j);
		}
	}
	return (0);
}
