/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/19 09:26:42 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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

float	calcule_light_intensity(t_scene *scene, t_surfaceinfo *info)
{
	float	constant;
	float	linear;
	float	quadratic;
	float	distance;
	float	attenuation;
	// long long		light_color;

	(void) scene;
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
	distance = vec_length(vec_sub(scene->light.pos, info->hit_point));
	attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));
	// ret = scene->light.brightness * scene->light.color / (4 * M_PI * powf(info->hit_dist, 2));
	// light_color = 10000;
	// printf("%i, %i, %i\n", get_r(light_color), get_g(light_color), get_b(light_color));
	// ret = scene->light.brightness * light_color / (4 * M_PI * powf(info->hit_dist, 2));
	// printf("light.color : %lli\n", light_color);
	// printf("ret : %f\n", ret);
	return (attenuation);
}

int	shading(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	float	f_ratio;
	float	spec;
	float	spec_intensity;
	float	attenuation;
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
	vis = shadow_visibility(scene, inter, info);
	if (!vis)
		f_ratio = 0;
	else
		f_ratio = ft_max(0.0f, vec_dot(info->hit_normal, vec_normalize(vec_scale(scene->light.pos, -1))));
	if (vis)
		attenuation = calcule_light_intensity(scene, info);
	else
		attenuation = 1;
	attenuation = 1;
	// (void) attenuation;
	// printf("light : %f, attenuation : %f\n", scene->light.brightness, attenuation);
	ambient = vec_scale(ambient, attenuation);
	diffuse = vec_scale(vec_scale(vec_color(scene->light.color), f_ratio), scene->light.brightness);
	diffuse = vec_scale(diffuse, attenuation);
	reflect_dir = reflect(scene->light.pos, info->hit_normal);
	spec = powf(ft_max(0.0f, vec_dot(info->view_dir, reflect_dir)), 16);
	// I added this condition to remove specular reflection in unrealistic places
	if (vis)
	{
		specular = vec_scale(spec_color, spec_intensity * spec);
		specular = vec_scale(specular, attenuation);
	}
	else
		specular = vec_scale(spec_color, f_ratio);
	// specular = set_vec(0, 0, 0);
	result = vec_mult(vec_add(vec_add(ambient, diffuse), specular), obj_color);
	if (result.x > 1)
		result.x = 1;
	if (result.y > 1)
		result.y = 1;
	if (result.z > 1)
		result.z = 1;
	return (int_color(result));
}