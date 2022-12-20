/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:32:56 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/20 21:30:34 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	// matrix_transformation(); one for ray.origin
	// matrix_transformation(); other for ray.dir
	ray.dir = vec_sub(pixel_camera, ray.origin);
	ray.dir = vec_normalize(ray.dir);
	// printf("raydir(%i)(%i): (%f %f %f)\n", x, y, ray.dir.x, ray.dir.y, ray.dir.z);
	return (ray);
}

int	interset(t_ray ray, t_scene *scene)
{
	(void) ray;
	(void) scene;
	return (1);
}

void	compute_pixel(t_scene *scene, t_vec3 *framebuffer, int i, int j)
{
	// int		k;
	t_ray	ray;

	(void) framebuffer;
	// k = -1;
	ray = build_camera_ray(scene, i, j);
	(void) ray;
	// while (++k < scene->num_objects_in_scene)
	// {
		// ray = build_camera_ray(i, j);
		// if (interset(ray, scene))
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

int	render(t_img *img, t_scene *scene)
{
	int		i;
	int		j;
	t_vec3	*framebuffer;

	i = -1;
	j = -1;
	(void) img;
	framebuffer = malloc(sizeof(t_vec3) * scene->win_h * scene->win_w);
	if (!framebuffer)
		return (EXIT_FAILURE);
	while (++j < scene->win_h)
	{
		i = -1;
		while (++i < scene->win_w)
		{
			compute_pixel(scene, framebuffer, i, j);
			my_mlx_pixel_put(img, i, j, scene->bg_color); // test color red
		}
	}
	free(framebuffer);
	return (0);
}
