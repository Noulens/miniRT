/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:13:08 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/31 10:22:33 by hyunah           ###   ########.fr       */
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

t_vec3	get_length_texture(t_pl *pl, t_vec3 a, t_vec3 b, t_vec3 hit)
{
	t_ray	ray1;
	t_ray	ray2;
	t_vec3	intersect_point;
	t_vec3	point;

	point = set_vec(0, 0, 0);
	ray1.origin = set_vec_point_dir(point, vec_normalize(a), 1.00);
	ray1.dir = set_vec_point_dir(point, vec_normalize(a), 2.00);
	point = vec_sub(hit, pl->translate);
	ray2.origin = set_vec_point_dir(point, vec_normalize(b), 1.00);
	ray2.dir = set_vec_point_dir(point, vec_normalize(b), 2.00);
	if (query_intersection(ray1, ray2, &intersect_point))
		return (intersect_point);
	return (set_vec(0, 0, 0));
}

void	hit_normal_plane(t_surfaceinfo *info, t_pl *pl)
{
	t_vec3	vec_null;
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	u_point;
	t_vec3	v_point;

	vec_null = set_vec(0.0, 0.0, 0.0);
	info->hit_normal = from_two_vec_do_rotation(set_vec(0, 1, 0), \
	pl->orientation, set_vec(0, 1, 0));
	if (BONUS == 1)
	{
		u_axis = from_two_vec_do_rotation(set_vec(0, 1, 0), pl->orientation, \
		set_vec(1, 0, 0));
		matrix_vec_mult(set_transform2(&vec_null, &pl->rotate), &u_axis);
		v_axis = from_two_vec_do_rotation(set_vec(0, 1, 0), pl->orientation, \
		set_vec(0, 0, 1));
		matrix_vec_mult(set_transform2(&vec_null, &pl->rotate), &v_axis);
		u_point = get_length_texture(pl, u_axis, v_axis, info->hit_point);
		v_point = get_length_texture(pl, v_axis, u_axis, info->hit_point);
		if (vec_dot((u_point), (u_axis)) < 0)
			info->hit_uv.y = -1 * vec_length(v_point);
		else
			info->hit_uv.y = vec_length(v_point);
		if (vec_dot((v_point), (v_axis)) < 0)
			info->hit_uv.x = -1 * vec_length(u_point);
		else
			info->hit_uv.x = vec_length(u_point);
	}
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
