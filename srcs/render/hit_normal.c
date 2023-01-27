/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:13:08 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/27 00:13:31 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	hit_normal_sphere(t_surfaceinfo *info, t_stdobj *obj)
{
	t_sp		*sphere;

	sphere = (t_sp *)obj->obj;
	info->hit_normal = vec_normalize(vec_sub(info->hit_point, sphere->pos));
	info->hit_uv.x = (1 + atan2f(info->hit_normal.z, \
	info->hit_normal.x) / (float)M_PI) * 0.5f;
	info->hit_uv.y = acosf(info->hit_normal.y) / (float)M_PI;
	info->hit_uv.z = 0;
}

void	hit_normal_plane(t_surfaceinfo *info, t_stdobj *obj)
{
	t_pl		*plane;

	plane = (t_pl *)obj->obj;
	info->hit_normal = vec_normalize(plane->orientation);
}

float	inverse_rot(float f, t_vec3 rot)
{

}

float	inverse_trans(float f, t_vec3 rot)
{

}

void	hit_uv_cyl(t_scene *s, t_surfaceinfo *info, t_cy *cyl)
{
	t_vec3	no_orient;
	float	x;
	float	y;
	float	z;
	float	angle;
	t_vec3	vec_null;
	t_vec3	inv_rotate;
	// t_vec3	middle_dot = vec_sub(info->hit_point, vec_scale(vec_scale(info->hit_normal, -1), cyl->diameter / 2));

	vec_null = set_vec(0, 0, 0);
	inv_rotate = vec_scale(cyl->rotate, -1);
	no_orient = vec_sub(info->hit_point, cyl->pos);
	set_transform(&vec_null, &inv_rotate, s);
	matrix_vec_mult(s->fwtfm, &no_orient);

	angle = atan2(no_orient.z, no_orient.x);
	info->hit_uv.x = angle / 2 * M_PI * (cyl->diameter / 2);
	info->hit_uv.y = no_orient.y / cyl->height;
	// print_vec(&cyl->orientation);
	// print_vec(&cyl->pos);
	// print_vec(&cyl->rotate);
	// printf("%f\n", cyl->diameter);
	// printf("%f\n", cyl->height);
}

void	hit_normal_cyl(t_scene *s, t_surfaceinfo *info, t_stdobj *obj)
{
	t_cy	*cyl;
	float	t;
	t_vec3	pt;
	t_vec3	top;
	t_vec3	bom;

	cyl = (t_cy *)obj->obj;
	top = vec_add(cyl->pos, vec_scale(cyl->orientation, cyl->height / 2.0f));
	bom = vec_sub(cyl->pos, vec_scale(cyl->orientation, cyl->height / 2.0f));
	if (vec_length(vec_sub(info->hit_point, top)) < cyl->diameter / 2)
		info->hit_normal = cyl->orientation;
	else if (vec_length(vec_sub(info->hit_point, bom)) < cyl->diameter / 2)
		info->hit_normal = vec_scale(cyl->orientation, -1.0f);
	else
	{
		t = vec_dot(vec_sub(info->hit_point, cyl->pos), cyl->orientation);
		pt = vec_add(cyl->pos, vec_scale(cyl->orientation, t));
		info->hit_normal = vec_normalize(vec_sub(info->hit_point, pt));
	}
	hit_uv_cyl(s, info, cyl);
}
