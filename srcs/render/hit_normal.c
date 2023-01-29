/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:13:08 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/29 22:06:03 by hyunah           ###   ########.fr       */
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

t_vec3	from_two_vec_do_rotation(t_vec3 origin1, t_vec3 target1, t_vec3 origin2)
{
	float	angle;
	t_vec3	perpendicular_axis;
	t_vec3	target2;

	(void)angle;
	(void)origin2;
	if (vec_compt(origin1, target1, 2))
		return (origin2);
	origin1 = vec_normalize(origin1);
	target1 = vec_normalize(target1);
	perpendicular_axis = vec_cross(origin1, vec_normalize(target1));
	if (vec_length(perpendicular_axis) != 0)
	{
		perpendicular_axis = vec_normalize(perpendicular_axis);
		angle = acosf(vec_dot(origin1, vec_normalize(target1)));
		if (origin2.x == 0 && origin2.y == 0 && origin2.z == 0)
			return (target1);
		target2 = rotate_from_axis_angle(origin2, perpendicular_axis, angle);
		return (target2);
	}
	return (set_vec(0, 0, 0));
}

float	get_length_texture(t_pl *pl, t_vec3 axis_u, t_vec3 axis_v, t_vec3 hit_point)
{
	t_ray	ray1;
	t_ray	ray2;
	t_vec3	intersect_point;

	// (void) intersect_point;
	// (void) hit_point;
	// (void) axis_v;
	// printf("axis_u:\n");
	// print_vec(&axis_u);
	ray1.origin = set_vec_point_dir(pl->translate, vec_normalize(axis_u), 1.00);
	ray1.dir = set_vec_point_dir(pl->translate, vec_normalize(axis_u), 3.00);
	// printf("ray1:\n");
	// print_vec(&ray1.origin);
	// print_vec(&ray1.dir);
	ray2.origin = set_vec_point_dir(hit_point, vec_normalize(axis_v), 1.00);
	ray2.dir = set_vec_point_dir(hit_point, vec_normalize(axis_v), 2.00);
	// printf("ray2:\n");
	// print_vec(&ray2.origin);
	// print_vec(&ray2.dir);
	// printf("\n");

	if (query_intersection(ray1, ray2, &intersect_point))
	{
		// print_vec(&intersect_point);
	// print_vec(&info->hit_point);
		return (vec_length(vec_sub(intersect_point, pl->translate)));
	}
	return (-1.0);
}

void	hit_normal_plane(t_surfaceinfo *info, t_stdobj *obj)
{
	t_pl		*plane;
	// t_vec3		vec_null;
	float		pattern;
	int			scale_v;
	int			scale_u;
	float	u;
	// float	v;
	t_vec3	axis_u;
	t_vec3	axis_v;

	// (void) vec_null;
	(void) scale_v;
	(void) scale_u;
	(void) axis_u;
	(void) axis_v;
	// (void) hit_point;
	scale_u = 1000;
	scale_v = 1000;
	plane = (t_pl *)obj->obj;
	info->hit_normal = vec_normalize(plane->orientation);
	axis_u = from_two_vec_do_rotation(set_vec(0, 1, 0), plane->orientation, set_vec(1, 0, 0));
	axis_v = from_two_vec_do_rotation(set_vec(0, 1, 0), plane->orientation, set_vec(0, 0, 1));
	// printf("%f\n", info->hit_dist);
	u = get_length_texture(plane, axis_u, axis_v, info->hit_point);
	// printf("u : %f\n", u);
	// inv_t = vec_add(info->hit_point, vec_scale(plane->translate, -1));
	// rot_m = set_transform2(&vec_null, &plane->rotate);
	// matrix_vec_mult(rot_m, &inv_t);
	// pattern = cos(to_radian(inv_t.z * scale_v)) * sin(to_radian(inv_t.x * scale_u));
	pattern = cos(to_radian(u * scale_v));
	pattern += 0.5;
	if (pattern >= 0.5f)
		info->hit_uv = set_vec(1, 1, 1);
	if (pattern < 0.5f)
		info->hit_uv = set_vec(0, 0, 0);
	// axis_u = rotate_from_axis_angle();
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
