/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/20 08:59:13 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	shadow_visibility(t_scene *s, t_func *inter, t_surfaceinfo *i, t_vec3 ldir)
{
	float	hit_dist;
	int		vis;
	t_ray	hit;

	hit.origin = vec_add(i->hit_point, vec_scale(i->hit_normal, 0.01f));
	hit.dir = vec_normalize(vec_scale(ldir, -1));
	vis = find_closest_obj(s, hit, inter, &hit_dist);
	if (vis == -1)
		return (1);
	else
		return (0);
}

void	get_pointlight_info(t_scene *s, t_surfaceinfo *i, t_vec3 *dir, float *f)
{
	t_vec3	light_dir;
	float	r2;

	light_dir = vec_sub(i->hit_point, s->light.pos);
	r2 = vec_length(light_dir);
	*dir = vec_normalize(light_dir);
	*f = s->light.brightness / (4 * M_PI * r2);
	/*
	printf("s->light.brightness: %f\n", s->light.brightness);
	printf("( 4 * M_PI * r2): %f\n", ( 4 * M_PI * r2));
	printf("intensity: %f\n", *f);
	printf("\n");
	*/
}

t_vec3	reflect(t_vec3 inv_lightdir, t_vec3 hit_normal)
{
	t_vec3	tmp;
	float	is_same_dir;

	is_same_dir = vec_dot(inv_lightdir, hit_normal);
	tmp = vec_scale(vec_scale(hit_normal, is_same_dir), 2);
	tmp = vec_sub(inv_lightdir, tmp);
	return (tmp);
}

t_vec3	calcule_specular(t_vec3 light_dir, t_surfaceinfo *info, int vis, float light_intensity)
{
	float	spec;
	t_vec3	r;
	t_vec3	result;
	int	spec_lightcolor;

	r = reflect(light_dir, info->hit_normal);
	spec_lightcolor = ft_trgb(255, 255, 255, 255);
	spec = vis * light_intensity * powf(ft_max(0.0f, vec_dot(r, info->view_dir)), 32);
	result = vec_scale(vec_color(spec_lightcolor), spec);
	if (result.x > 1)
		result.x = 1;
	if (result.y > 1)
		result.y = 1;
	if (result.z > 1)
		result.z = 1;
	return (result);
}

int	shading(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	float	light_intensity;
	float	face_ratio;
	int		vis;
	t_vec3	obj_color;
	t_vec3	diffuse;
	t_vec3	result;
	t_vec3	light_dir;
	t_vec3	ambient;
	t_vec3	specular;

	scene->light.exposure = 50;
	light_intensity = scene->light.brightness;
	obj_color = vec_scale(vec_color(scene->objtab[c_obj]->metacolor), 1 / M_PI);
	get_pointlight_info(scene, info, &light_dir, &light_intensity);
	light_intensity *= scene->light.exposure;
	vis = shadow_visibility(scene, inter, info, light_dir);
	face_ratio = ft_max(0.0f, vec_dot(info->hit_normal, vec_scale(light_dir, -1)));
	ambient = vec_scale(vec_color(scene->alight.color), scene->alight.al);
	diffuse = vec_scale(vec_color(scene->light.color), light_intensity);
	diffuse = vec_scale(vec_scale(diffuse, vis), face_ratio);
	specular = calcule_specular(light_dir, info, vis, light_intensity);
	// result = vec_add(diffuse, vec_mult(obj_color, ambient));
	result = vec_mult(vec_add(vec_add(diffuse, ambient), specular), obj_color);
	// vec_mult(obj_color, diffuse)
	return (int_color(result));
}