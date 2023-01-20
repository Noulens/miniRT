/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/20 10:39:08 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	shading(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	t_material	mat;
	float		light_intensity;
	int			vis;
	t_vec3		obj_color;
	t_vec3		light_dir;

	light_intensity = scene->light.brightness;
	obj_color = vec_scale(vec_color(scene->objtab[c_obj]->metacolor), 1 / M_PI);
	get_pointlight_info(scene, info, &light_dir, &light_intensity);
	light_intensity *= scene->light.exposure;
	vis = shadow_visibility(scene, inter, info, light_dir);
	mat.face_ratio = ft_max(0.0f, vec_dot(info->hit_normal, \
	vec_scale(light_dir, -1)));
	mat.ambient = vec_scale(vec_color(scene->alight.color), scene->alight.al);
	mat.diffuse = vec_scale(vec_color(scene->light.color), light_intensity);
	mat.diffuse = vec_scale(vec_scale(vec_mult(obj_color, mat.diffuse), vis), \
	mat.face_ratio);
	mat.result = vec_add(mat.diffuse, vec_mult(obj_color, mat.ambient));
	return (int_color(mat.result));
}
