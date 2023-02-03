/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 07:56:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/02 17:54:51 by tnoulens         ###   ########.fr       */
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

	exponent = 500;
	spec_lightcolor = ft_trgb(255, 255, 255, 255);
	r = reflect(lr, info->hit_normal);
	spec = vis * li * powf(ft_max(0.0f, vec_dot(r, info->view_dir)), exponent);
	result = vec_scale(vec_color(spec_lightcolor), spec);
	keep_between_zero_one_vector(&result);
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
		pattern = 1;
		*obj_color = vec_color(ft_trgb(255, 255, 255, 255));
	}
	return (pattern);
}

float	calcule_plan_pattern(t_surfaceinfo *info, t_vec3 *obj_color)
{
	float		pattern;
	float		scale_v;
	float		scale_u;
	float		u;
	float		v;

	u = info->hit_uv.x;
	v = info->hit_uv.y;
	scale_u = 0.5;
	scale_v = 0.5;
	pattern = (modulo(u * scale_u) > 0.5f) ^ (modulo(v * scale_v) > 0.5f);
	if (pattern >= 0.5f)
		pattern = 1;
	if (pattern < 0.5f)
	{
		pattern = 1;
		*obj_color = vec_color(ft_trgb(255, 255, 255, 255));
	}
	return (1);
}

int	shading(t_scene *scene, t_surfaceinfo *info, int c_obj, t_func *inter)
{
	t_material	mat;
	int			i;

	i = -1;
	mat.result = set_vec(0, 0, 0);
	mat.specular = set_vec(0, 0, 0);
	while (++i < scene->num_lamps)
	{
		scene->k = i;
		get_render_info(scene, info, c_obj, &mat);
		mat.vis = shadow_vis(scene, inter, info, mat.l_dir);
		if (scene->objtab[c_obj]->objtp == SP)
			calcule_sphere_pattern(info, &mat.obj_color);
		if (scene->objtab[c_obj]->objtp == PL)
			calcule_plan_pattern(info, &mat.obj_color);
		if (i == 0)
			mat.result = vec_scale(vec_mult(mat.obj_color, \
			vec_color(scene->alight.color)), scene->alight.al);
		mat.diffuse = vec_scale(vec_scale(vec_color(scene->lamptab[i]->color), \
						mat.vis * mat.l_inten), mat.face_ratio);
		mat.specular = calcule_specular(mat.l_dir, info, mat.vis, mat.l_inten);
		mat.result = vec_add(vec_mult((vec_add(mat.diffuse, mat.specular)), \
		mat.obj_color), mat.result);
	}
	return (keep_between_zero_one_vector(&mat.result), int_color(mat.result));
}
