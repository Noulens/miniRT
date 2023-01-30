/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/30 00:55:39 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_vec3	reflect(t_vec3 inv_lightdir, t_vec3 hit_normal)
{
	t_vec3	tmp;
	float	is_same_dir;

	is_same_dir = vec_dot(inv_lightdir, hit_normal);
	tmp = vec_scale(vec_scale(hit_normal, is_same_dir), 2);
	tmp = vec_sub(inv_lightdir, tmp);
	return (tmp);
}

t_vec3	calcule_specular(t_vec3 lr, t_surfaceinfo *info, int vis, float li)
{
	float	spec;
	t_vec3	r;
	t_vec3	result;
	int		spec_lightcolor;
	int		exponent;

	exponent = 32;
	spec_lightcolor = ft_trgb(255, 255, 255, 255);
	r = reflect(lr, info->hit_normal);
	spec = vis * li * powf(ft_max(0.0f, vec_dot(r, info->view_dir)), exponent);
	result = vec_scale(vec_color(spec_lightcolor), spec);
	if (result.x > 1)
		result.x = 1;
	if (result.y > 1)
		result.y = 1;
	if (result.z > 1)
		result.z = 1;
	return (result);
}

float	calcule_sphere_pattern(t_surfaceinfo *info, t_vec3 *obj_color)
{
	float	pattern;
	int		scale_u;
	int		scale_v;

	scale_u = 10;
	scale_v = 10;
	pattern = cos(info->hit_uv.y * 2 * M_PI * scale_v) * \
	sin(info->hit_uv.x * 2 * M_PI * scale_u) * 0.5;
	pattern += 0.5;
	if (pattern >= 0.5f)
		pattern = 1;
	if (pattern < 0.5f)
	{
		pattern = 0;
		*obj_color = vec_color(ft_trgb(255, 255, 255, 255));
	}
	return (pattern);
}

float	calcule_plan_pattern(t_surfaceinfo *info, t_vec3 *obj_color)
{
	// float	pattern;
	// int		scale_u;
	// int		scale_v;

	// scale_u = 1000;
	// scale_v = 1000;
	(void) obj_color;
	// pattern = cos(to_radian(info->hit_point.z * scale_v)) * 
	// sin(to_radian(info->hit_point.x * scale_u));
	// pattern += 0.5;
	// if (pattern >= 0.5f)
	// 	pattern = 1;
	// if (pattern < 0.5f)
	// 	pattern = 0;
	if (info->hit_uv.x)
		return (1);
	return (0);
}

// float	calcule_cyl_pattern(t_scene *s, int c_obj, t_surfaceinfo *info, t_vec3 *obj_color)
// {
// 	float	pattern;
// 	int		scale_u;
// 	int		scale_v;
// 	t_cy	*cy;
// 	float	ratio;
// 	cy = s->objtab[c_obj]->obj;
// 	ratio = cy->height / cy->diameter * M_PI;
// 	scale_v = 500;
// 	scale_u = scale_v * ratio;
// 	(void) obj_color;
// 	pattern = cos(to_radian(info->hit_uv.x * scale_v)) * sin(to_radian(info->hit_uv.y * scale_u));
// 	pattern += 0.5;
// 	if (pattern >= 0.5f)
// 		pattern = 1;
// 	if (pattern < 0.5f)
// 		pattern = 0;
// 	return (pattern);
// }

// float	calcule_cyl_pattern(t_surfaceinfo *info, t_vec3 *obj_color)
// {
// 	float	pattern;
// 	int		scale_u;
// 	int		scale_v;

// 	scale_u = 10;
// 	scale_v = 10;
// 	pattern = (modulo(info->hit_uv.y * scale_u) > 0.5f)
// 			^ (modulo(info->hit_uv.x * scale_v) > 0.5f);
// 	if (pattern >= 0.5f)
// 		pattern = 1;
// 	if (pattern < 0.5f)
// 	{
// 		pattern = 1;
// 		*obj_color = vec_color(ft_trgb(255, 255, 255, 255));
// 	}
// 	return (pattern);
// }

int	shading(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	t_material	mat;
	float		light_intensity;
	float		pattern;
	int			vis;
	int			i;
	t_vec3		obj_color;
	t_vec3		light_dir;

	i = -1;
	mat.result = set_vec(0, 0, 0);
	while (++i < scene->num_lamps)
	{
		scene->k = i;
		light_intensity = scene->lamptab[i]->brightness;
		obj_color = vec_color(scene->objtab[c_obj]->metacolor);
		get_pointl_info(scene, info, &light_dir, &light_intensity);
		light_intensity *= scene->lamp->exposure;
		vis = shadow_visibility(scene, inter, info, light_dir);
		mat.face_ratio = ft_max(0.0f, vec_dot(info->hit_normal, \
		vec_scale(light_dir, -1)));
		pattern = 1;
		if (scene->objtab[c_obj]->objtp == SP)
			pattern = calcule_sphere_pattern(info, &obj_color);
		if (scene->objtab[c_obj]->objtp == PL)
			pattern = calcule_plan_pattern(info, &obj_color);
		// if (scene->objtab[c_obj]->objtp == CY)
			// pattern = calcule_cyl_pattern(scene, c_obj, info, &obj_color);
		mat.diffuse = vec_scale(vec_scale(vec_color(scene->lamptab[i]->color), \
						vis * light_intensity * pattern), mat.face_ratio);
		mat.specular = calcule_specular(light_dir, info, vis, light_intensity);
		mat.result = vec_add(vec_mult((vec_add(mat.diffuse, mat.specular)), obj_color), mat.result);
	}
	mat.ambient = vec_scale(vec_color(scene->alight.color), \
	scene->alight.al);
	mat.result = vec_scale(vec_add(mat.result, mat.ambient), 0.5f);
	if (mat.result.x > 1)
		mat.result.x = 1;
	if (mat.result.y > 1)
		mat.result.y = 1;
	if (mat.result.z > 1)
		mat.result.z = 1;
	return (int_color(mat.result));
}
