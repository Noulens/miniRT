/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/01 09:59:28 by hyunah           ###   ########.fr       */
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
	(float)mat.vis * mat.face_ratio * mat.l_inten);
	mat.result = vec_add(mat.ambient, mat.diffuse);
	keep_between_zero_one_vector(&mat.result);
	return (int_color(mat.result));
}
