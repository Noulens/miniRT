/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:13:08 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/30 21:50:22 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_vec3	from_two_vec_do_rotation(t_vec3 origin1, t_vec3 target1, t_vec3 origin2)
{
	float	angle;
	float	dot;
	t_vec3	perpendicular_axis;
	t_vec3	target2;
	t_vec3	vec_null;
	t_vec3	rot;

	(void)dot;
	if (vec_compt(origin1, target1, 2))
		return (origin2);
	origin1 = vec_normalize(origin1);
	target1 = vec_normalize(target1);
	perpendicular_axis = vec_cross(origin1, vec_normalize(target1));
	dot = vec_dot(origin1, vec_normalize(target1));
	if (vec_length(perpendicular_axis) != 0)
	{
		perpendicular_axis = vec_normalize(perpendicular_axis);
		angle = acosf(vec_dot(origin1, vec_normalize(target1)));
		if (origin2.x == 0 && origin2.y == 0 && origin2.z == 0)
			return (target1);
		target2 = rotate_from_axis_angle(origin2, perpendicular_axis, angle);
		return (target2);
	}
	vec_null = set_vec(0, 0, 0);
	rot = set_vec(0, 180, 0);
	target2 = set_vec(origin2.x, origin2.y, origin2.z);
	matrix_vec_mult(set_transform2(&vec_null, &rot), &target2);
	return (target2);
}

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
	top = vec_add(cyl->pos, vec_scale(cyl->orientation, cyl->height));
	bom = cyl->pos;
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
