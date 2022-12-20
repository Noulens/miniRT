/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:32:56 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/19 20:05:11 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*offset;

	offset = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)offset = color;
}

t_ray	build_camera_ray(int i, int j)
{
	t_ray	ray;

	(void) i;
	(void) j;
	return (ray);
}

int	interset(t_ray ray, t_scene *scene)
{
	(void) ray;
	(void) scene;
	return (1);
}

void	compute_pixel(t_scene *scene, t_vec *framebuffer, int i, int j)
{
	int		k;
	t_ray	ray;

	(void) framebuffer;
	k = -1;
	while (++k < scene->num_objects_in_scene)
	{
		ray = build_camera_ray(i, j);
		if (interset(ray, scene))
		{
			// do complex shading here but for now basic (just constant color)
			// framebuffer[j * scene->win_w + i] = scene->objects[k].color;
		}
		else
		{
			// or don't do anything and leave it black
			// framebuffer[j * scene->win_w + i] = scene->bg_color;
		}
	}
}

int	render(t_img *img, t_scene *scene)
{
	int		i;
	int		j;
	t_vec	*framebuffer;

	i = -1;
	j = -1;
	framebuffer = malloc(sizeof(t_vec) * scene->win_h * scene->win_w);
	if (!framebuffer)
		return (EXIT_FAILURE);
	while (++i < scene->win_h)
	{
		j = -1;
		while (++j < scene->win_w)
		{
			compute_pixel(scene, framebuffer, i, j);
			my_mlx_pixel_put(img, j, i, scene->bg_color); // test color red
		}
	}
	free(framebuffer);
	return (0);
}
