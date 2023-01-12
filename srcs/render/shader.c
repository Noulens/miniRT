/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/12 15:26:06 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

float	ft_max(float a, float b)
{
	if (a <= b)
		return (b);
	return (a);
}

void	get_surfaceinfo_sphere(t_surfaceinfo *info, t_stdobj *obj, t_ray ray)
{
	t_sp		*sphere;

	sphere = (t_sp *)obj->obj;
	info->hit_point = vec_add(ray.origin, vec_scale(ray.dir, info->hit_dist));
	info->hit_normal = vec_normalize(vec_sub(info->hit_point, sphere->pos));
	info->view_dir = vec_normalize(vec_scale(ray.dir, -1));
	return ;
}

void	get_surfaceinfo_plane(t_surfaceinfo *info, t_stdobj *obj, t_ray ray)
{
	t_pl		*plane;

	plane = (t_pl *)obj->obj;
	info->hit_normal = vec_normalize(plane->orientation);
	info->hit_point = vec_add(ray.origin, vec_scale(ray.dir, info->hit_dist));
	info->view_dir = vec_normalize(vec_scale(ray.dir, -1));
	return ;
}

t_surfaceinfo	*get_surfaceinfo(t_surfaceinfo *info, t_stdobj *obj, t_ray ray)
{
	if (obj->objtp == 0)
		get_surfaceinfo_sphere(info, obj, ray);
	if (obj->objtp == 2)
		get_surfaceinfo_plane(info, obj, ray);
	return (info);
}

int	lambert(t_scene *scene, t_surfaceinfo info, int closest_obj, t_func *inter)
{
	float	facing_ratio;
	float	hit_dist;
	t_ray	hit;
	int		vis;
	int		r;
	int		g;
	int		b;
	float	light_intensity;
	t_vec3	light_dir;

	light_dir = vec_scale(set_vec(0.3, -1, -0.5), -1);
	// TODO: replace by variable.
	light_intensity = 1;
	// light_color = ft_trgb(255, 0, 0, 0);
	facing_ratio = ft_max(0.0f, vec_dot(info.hit_normal, vec_normalize(light_dir)));
	hit.origin = vec_add(info.hit_point, vec_scale(info.hit_normal, 0.01f));
	hit.dir = light_dir;
	vis = find_closest_obj(scene, hit, inter, &hit_dist);
	if (vis == -1)
		vis = 1;
	else
		vis = 0;
	r = get_r(scene->objtab[closest_obj]->metacolor) * facing_ratio * light_intensity *vis;
	if (r > 255)
		r = 255;
	g = get_g(scene->objtab[closest_obj]->metacolor) * facing_ratio * light_intensity *vis;
	if (g > 255)
		g = 255;
	b = get_b(scene->objtab[closest_obj]->metacolor) * facing_ratio * light_intensity *vis;
	if (b > 255)
		b = 255;
	return (ft_trgb(255, r, g, b));
}