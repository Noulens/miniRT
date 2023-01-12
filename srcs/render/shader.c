/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/12 17:08:44 by hyunah           ###   ########.fr       */
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

int	shadow_visibility(t_scene *scene, t_func *inter, t_surfaceinfo *info)
{
	float	hit_dist;
	int		vis;
	t_ray	hit;

	hit.origin = vec_add(info->hit_point, vec_scale(info->hit_normal, 0.01f));
	hit.dir = vec_scale(set_vec(0.3, -1, -0.5), -1); // light direction
	vis = find_closest_obj(scene, hit, inter, &hit_dist);
	if (vis == -1)
		return (1);
	else
		return (0);
}

int	lambert(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	float	f_ratio;
	int		vis;
	int		r;
	int		g;
	int		b;
	float	l_int;
	t_vec3	light_dir;

	/* TODO: replace by variable.*/
	l_int = 1;
	// light_color = ft_trgb(255, 0, 0, 0);
	light_dir = vec_scale(set_vec(0.3, -1, -0.5), -1); // light directio
	f_ratio = ft_max(0.0f, vec_dot(info->hit_normal, vec_normalize(light_dir)));
	vis = shadow_visibility(scene, inter, info);
	r = get_r(scene->objtab[c_obj]->metacolor) * f_ratio * l_int * vis;
	if (r > 255)
		r = 255;
	g = get_g(scene->objtab[c_obj]->metacolor) * f_ratio * l_int * vis;
	if (g > 255)
		g = 255;
	b = get_b(scene->objtab[c_obj]->metacolor) * f_ratio * l_int * vis;
	if (b > 255)
		b = 255;
	return (ft_trgb(255, r, g, b));
}