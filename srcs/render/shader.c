/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/23 16:02:55 by hyunah           ###   ########.fr       */
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

	light_intensity = scene->lamp->brightness;
	obj_color = vec_color(scene->objtab[c_obj]->metacolor);
	get_pointlight_info(scene, info, &light_dir, &light_intensity, 0);
	vis = shadow_visibility(scene, inter, info, light_dir);
	mat.face_ratio = ft_max(0.0f, vec_dot(info->hit_normal, \
	vec_scale(light_dir, -1)));
	light_intensity *= scene->lamp->exposure;
	mat.ambient = vec_scale(vec_mult(obj_color, vec_color(scene->alight.color)), scene->alight.al);
	mat.diffuse = vec_scale(vec_mult(obj_color, vec_color(scene->lamp->color)), vis * mat.face_ratio * light_intensity);
	mat.result = vec_scale(vec_add(mat.ambient, mat.diffuse), 0.5);
	if (mat.result.x > 1)
		mat.result.x = 1;
	if (mat.result.y > 1)
		mat.result.y = 1;
	if (mat.result.z > 1)
		mat.result.z = 1;
	return (int_color(mat.result));
}
