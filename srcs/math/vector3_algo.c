/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:50:45 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/29 23:38:56 by hyunah           ###   ########.fr       */
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

int	vec_compt(t_vec3 a, t_vec3 b, int precision)
{
	int	x_same;
	int	y_same;
	int	z_same;

	x_same = 0;
	y_same = 0;
	z_same = 0;
	a = vec_scale(a, pow(10, precision));
	b = vec_scale(b, pow(10, precision));
	if (roundf(a.x) == roundf(b.x))
		x_same = 1;
	if (roundf(a.y) == roundf(b.y))
		y_same = 1;
	if (roundf(a.z) == roundf(b.z))
		z_same = 1;
	if (x_same && y_same && z_same)
		return (1);
	return (0);
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

t_vec3	set_vec_point_dir(t_vec3 point, t_vec3 dir, float t)
{
	t_vec3	v;
	t_vec3	orient;

	orient = vec_normalize(dir);
	v.x = point.x + (t * orient.x);
	v.y = point.y + (t * orient.y);
	v.z = point.z + (t * orient.z);
	return (v);
}
