/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:32:56 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/30 01:12:54 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_surfaceinfo	*get_surfaceinfo(t_surfaceinfo *info, t_stdobj *obj, t_ray ray)
{
	info->view_dir = vec_normalize(vec_scale(ray.dir, -1));
	info->hit_point = vec_add(ray.origin, vec_scale(ray.dir, info->hit_dist));
	if (obj->objtp == 0)
		hit_normal_sphere(info, obj);
	if (obj->objtp == 2)
		hit_normal_plane(info, obj);
	if (obj->objtp == 1)
		hit_normal_cyl(info, obj);
	return (info);
}

int	compute_pixel(t_scene *s, int i, int j, t_func *inter)
{
	t_ray			ray;
	int				closest_obj;
	t_surfaceinfo	info;

	closest_obj = -1;
	s->x = i;
	s->y = j;
	ray = build_camera_ray(s, i, j);
	closest_obj = find_closest_obj(s, ray, inter, &info.hit_dist);
	if (closest_obj != -1)
	{
		get_surfaceinfo(&info, s->objtab[closest_obj], ray);
		if (s->objtab[closest_obj]->objtp == 0 \
		|| s->objtab[closest_obj]->objtp == 2 || \
		s->objtab[closest_obj]->objtp == 1)
			my_mlx_pixel_put(s->ig, i, j, \
			shading(s, &info, closest_obj, inter));
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
