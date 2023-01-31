/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/31 15:06:37 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	shading(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	t_material	mat;

	get_render_info(scene, info, c_obj, &mat);
	mat.vis = shadow_vis(scene, inter, info, mat.l_dir);
	mat.ambient = vec_scale(vec_mult(mat.obj_color, \
	vec_color(scene->alight.color)), scene->alight.al);
	mat.diffuse = vec_scale(vec_mult(mat.obj_color, \
	vec_color(scene->lamp->color)), \
	(float)mat.vis * mat.face_ratio * mat.l_intensity);
	mat.result = vec_scale(vec_add(mat.ambient, mat.diffuse), 0.5f);
	keep_between_zero_one(&mat.result.x);
	keep_between_zero_one(&mat.result.y);
	keep_between_zero_one(&mat.result.z);
	return (int_color(mat.result));
}
