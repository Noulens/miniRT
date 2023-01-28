/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:13:08 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/28 23:07:21 by hyunah           ###   ########.fr       */
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
	t_vec3		vec_null;
	float		pattern;
	int			scale_v;
	int			scale_u;
	t_vec3	orient_parsing;
	t_vec3	plane_n;
	float	angle;
	t_vec3	t;
	t_vec3	axis;
	t_matrix4	rot_m;

	(void) vec_null;
	scale_u = 1000;
	scale_v = 1000;
	vec_null = set_vec(0, 0, 0);
	plane = (t_pl *)obj->obj;
	plane_n = set_vec(0, 1, 0);
	orient_parsing = vec_normalize(plane->orientation);
	t = vec_cross(plane_n, vec_normalize(orient_parsing));
	if (vec_length(t) != 0)
	{
		axis = vec_normalize(t);
		angle = acosf(vec_dot(plane_n, vec_normalize(orient_parsing)));
		plane_n = rotate_from_axis_angle(plane_n, axis, angle);
	}
	matrix_vec_mult(set_transform2(&vec_null, &plane->rotate), &plane_n);
	info->hit_normal = vec_normalize(plane_n);
	t_vec3	inv_t;

	inv_t = vec_add(info->hit_point, vec_scale(plane->translate, -1));
	rot_m = set_transform2(&vec_null, &plane->rotate);
	matrix_vec_mult(rot_m, &inv_t);
	pattern = cos(to_radian(inv_t.z * scale_v)) * \
	sin(to_radian(inv_t.x * scale_u));
	pattern += 0.5;
	if (pattern >= 0.5f)
		info->hit_uv = set_vec(1, 1, 1);
	if (pattern < 0.5f)
		info->hit_uv = set_vec(0, 0, 0);

}

/*
void	hit_uv_cyl(t_surfaceinfo *info, t_cy *cyl)
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
*/

void	hit_normal_cyl(t_surfaceinfo *info, t_stdobj *obj)
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
}
