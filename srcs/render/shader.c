/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/13 15:18:46 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	hit_normal_sphere(t_surfaceinfo *info, t_stdobj *obj)
{
	t_sp		*sphere;

	sphere = (t_sp *)obj->obj;
	info->hit_normal = vec_normalize(vec_sub(info->hit_point, sphere->pos));
	return ;
}

void	hit_normal_plane(t_surfaceinfo *info, t_stdobj *obj)
{
	t_pl		*plane;

	plane = (t_pl *)obj->obj;
	info->hit_normal = vec_normalize(plane->orientation);
	return ;
}

t_surfaceinfo	*get_surfaceinfo(t_surfaceinfo *info, t_stdobj *obj, t_ray ray)
{
	info->view_dir = vec_normalize(vec_scale(ray.dir, -1));
	info->hit_point = vec_add(ray.origin, vec_scale(ray.dir, info->hit_dist));
	if (obj->objtp == 0)
		hit_normal_sphere(info, obj);
	if (obj->objtp == 2)
		hit_normal_plane(info, obj);
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

t_vec3	reflect(t_vec3 inv_lightdir, t_vec3 hit_normal)
{
	t_vec3	tmp;
	float	f;

	f = vec_dot(inv_lightdir, hit_normal);
	tmp = vec_scale(vec_scale(hit_normal, f), 2);
	tmp = vec_sub(inv_lightdir, tmp);
	return (tmp);
}

int	shading(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	float	f_ratio;
	float	spec;
	float	spec_intensity;
	int		vis;
	t_vec3	specular;
	t_vec3	spec_color;
	t_vec3	reflect_dir;
	t_vec3	ambient;
	t_vec3	result;
	t_vec3	obj_color;
	t_vec3	diffuse;

	//light color doesn't work
	//rgb overflow
	spec_intensity = 0.2f;
	spec_color = set_vec(1.0f, 1.0f, 1.0f);
	ambient = vec_scale(vec_color(scene->alight.color), scene->alight.al);
	obj_color = vec_color(scene->objtab[c_obj]->metacolor);
	f_ratio = ft_max(0.0f, vec_dot(info->hit_normal, vec_normalize(vec_scale(scene->light.pos, -1))));
	vis = shadow_visibility(scene, inter, info);
	if (!vis)
		f_ratio = 0;
	diffuse = vec_scale(vec_color(scene->light.color), f_ratio);
	reflect_dir = reflect(scene->light.pos, info->hit_normal);
	spec = powf(ft_max(0.0f, vec_dot(info->view_dir, reflect_dir)), 16);
	// I added this condition to remove specular reflection in unrealistic places
	if (vis)
		specular = vec_scale(spec_color, spec_intensity * spec);
	else
		specular = vec_scale(spec_color, f_ratio);
	result = vec_mult(vec_add(vec_add(ambient, diffuse), specular), obj_color);
	if (result.x > 1)
		result.x = 1;
	if (result.y > 1)
		result.y = 1;
	if (result.z > 1)
		result.z = 1;
	return (int_color(result));
}