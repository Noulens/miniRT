/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:50:45 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/31 09:40:00 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

t_vec3	rotate_from_axis_angle(t_vec3 vector, t_vec3 axis, float angle)
{
	t_vec3	d;
	t_vec3	r;
	t_vec3	rcos;
	t_vec3	axiscross;
	t_vec3	ssin;

	if (vector.x == 0 && vector.y == 0 && vector.z == 0)
		return (vector);
	axis = vec_normalize(axis);
	d = vec_scale(axis, vec_dot(axis, vector));
	r = vec_sub(vector, d);
	rcos = vec_scale(r, cosf(angle));
	axiscross = vec_cross(axis, r);
	ssin = vec_scale(axiscross, sinf(angle));
	return (vec_add(vec_add(ssin, rcos), d));
}

t_vec3	get_contact_point(t_vec3 normal, t_vec3 planedot, t_vec3 a, t_vec3 b)
{
	t_vec3	nab;
	float	tmp1;
	t_vec3	tmp2;

	nab = vec_normalize(vec_sub(b, a));
	tmp1 = vec_dot(normal, vec_sub(planedot, a)) / vec_dot(normal, nab);
	tmp2 = vec_scale(nab, tmp1);
	return (vec_add(a, tmp2));
}

int	query_intersection(t_ray ray1, t_ray ray2, t_vec3 *intersect_point)
{
	t_vec3	ret;
	t_vec3	ab;
	t_vec3	cd;
	t_vec3	cross_nab;
	t_vec3	cross_ncd;

	ab = vec_sub(ray1.origin, ray1.dir);
	cd = vec_sub(ray2.origin, ray2.dir);
	cross_nab = vec_cross(vec_cross(ab, cd), ab);
	cross_ncd = vec_cross(vec_cross(ab, cd), cd);
	ret = get_contact_point(cross_nab, ray1.origin, ray2.origin, ray2.dir);
	if (vec_compt(ret, \
	get_contact_point(cross_ncd, ray2.origin, ray1.origin, ray1.dir), 2))
	{
		intersect_point->x = ret.x;
		intersect_point->y = ret.y;
		intersect_point->z = ret.z;
		return (1);
	}
	return (0);
}

t_vec3	opposite_direction(t_vec3 target1, t_vec3 origin2)
{
	t_vec3	vec_null;
	t_vec3	rot;
	t_vec3	target2;

	if (vec_compt(target1, set_vec(0, 0, 1), 2))
		rot = set_vec(0, 180, 0);
	if (vec_compt(target1, set_vec(0, -1, 0), 2))
		rot = set_vec(0, 0, 180);
	vec_null = set_vec(0, 0, 0);
	target2 = set_vec(origin2.x, origin2.y, origin2.z);
	matrix_vec_mult(set_transform2(&vec_null, &rot), &target2);
	return (target2);
}

t_vec3	from_two_vec_do_rotation(t_vec3 origin1, t_vec3 target1, t_vec3 origin2)
{
	float	angle;
	t_vec3	perpendicular_axis;
	t_vec3	target2;

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
	target2 = opposite_direction(target1, origin2);
	return (target2);
}
