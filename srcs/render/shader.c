/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/13 10:51:27 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	get_surfaceinfo_sphere(t_surfaceinfo *info, t_stdobj *obj, t_ray ray)
{
	t_sp		*sphere;

	sphere = (t_sp *)obj->obj;
	info->hit_point = vec_add(ray.origin, vec_scale(ray.dir, info->hit_dist));
	info->hit_normal = vec_normalize(vec_sub(info->hit_point, sphere->pos));
	return ;
}

void	get_surfaceinfo_plane(t_surfaceinfo *info, t_stdobj *obj, t_ray ray)
{
	t_pl		*plane;

	plane = (t_pl *)obj->obj;
	info->hit_normal = vec_normalize(plane->orientation);
	info->hit_point = vec_add(ray.origin, vec_scale(ray.dir, info->hit_dist));
	return ;
}

t_surfaceinfo	*get_surfaceinfo(t_surfaceinfo *info, t_stdobj *obj, t_ray ray)
{
	info->view_dir = vec_normalize(vec_scale(ray.dir, -1));
	if (obj->objtp == 0)
		get_surfaceinfo_sphere(info, obj, ray);
	if (obj->objtp == 2)
		get_surfaceinfo_plane(info, obj, ray);
	return (info);
}

int	shadow_visibility(t_scene *scene, t_func *inter, t_surfaceinfo *info)
{
	float	hit_dist;
	int		vis;
	t_ray	hit;

	hit.origin = vec_add(info->hit_point, vec_scale(info->hit_normal, 0.01f));
	hit.dir = vec_scale(scene->light.pos, -1);
	vis = find_closest_obj(scene, hit, inter, &hit_dist);
	if (vis == -1)
		return (1);
	else
		return (0);
}

int	lambert(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	// float	f_ratio;
	// int		vis;
	// int		r;
	// int		g;
	// int		b;
	t_vec3	result;
	// t_vec3	color;
	// int	colorint;
	(void) info;
	(void) scene;
	(void) c_obj;
	(void) inter;
	// color = vec_color(get_r(scene->alight.color), get_g(scene->alight.color), get_b(scene->alight.color));
	// print_vec(&color);
	// colorint = scene->alight.color;
	// printf("%i %i %i\n", get_r(colorint), get_g(colorint), get_b(colorint));
	result = vec_scale(vec_color(scene->alight.color), scene->alight.al);
	// f_ratio = ft_max(0.0f, vec_dot(info->hit_normal, vec_normalize(vec_scale(scene->light.pos, -1))));
	// vis = shadow_visibility(scene, inter, info);
	// r = get_r(scene->objtab[c_obj]->metacolor) * f_ratio * scene->light.brightness * vis;
	// if (r > 255)
	// 	r = 255;
	// g = get_g(scene->objtab[c_obj]->metacolor) * f_ratio * scene->light.brightness * vis;
	// if (g > 255)
	// 	g = 255;
	// b = get_b(scene->objtab[c_obj]->metacolor) * f_ratio * scene->light.brightness * vis;
	// if (b > 255)
	// 	b = 255;
	return (ft_trgb(255, result.x, result.y, result.z));
}