/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 05:59:59 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/13 09:37:55 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	intersect_sphere2(float tca, float thc, float *hit_distance)
{
	float		t0;
	float		t1;

	t0 = tca - thc;
	t1 = tca + thc;
	if (t0 > t1)
		ft_swap(&t0, &t1);
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (0);
	}
	*hit_distance = t0;
	return (1);
}

int	intersect_sphere(t_ray ray, t_stdobj *tmp, float *hit_distance)
{
	float		tca;
	float		thc;
	float		d2;
	t_vec3		l;
	t_sp		*sphere;

	sphere = (t_sp *)tmp->obj;
	sphere->radius = sphere->diameter / 2.0f;
	l = vec_sub(sphere->pos, ray.origin);
	tca = vec_dot(l, ray.dir);
	if (tca < 0)
		return (0);
	d2 = vec_dot(l, l) - tca * tca;
	if (d2 > sphere->radius)
		return (0);
	thc = sqrtf(sphere->radius - d2);
	return (intersect_sphere2(tca, thc, hit_distance));
}

int	intersect_plane(t_ray ray, t_stdobj *tmp, float *hit_distance)
{
	t_pl	*plane;
	t_vec3	plane_n;
	t_vec3	intersect_pos;
	float	denom;
	float	dist_btw_cam_planeinter;

	plane = (t_pl *)tmp->obj;
	plane_n = plane->orientation;
	denom = vec_dot(plane_n, ray.dir);
	if (denom != 0)
	{
		intersect_pos = vec_sub(plane->pos, ray.origin);
		dist_btw_cam_planeinter = vec_dot(intersect_pos, plane_n) / denom;
		*hit_distance = dist_btw_cam_planeinter;
		return (dist_btw_cam_planeinter >= 0);
	}
	return (0);
}
// THIS CODE ONLY WORKS FOR INFINITE CYLINDERS
//static void	check_for_solutions_cylinder(float *dist)
//{
//	if (dist[ROOT1] > dist[ROOT2])
//		ft_swap(&dist[ROOT1], &dist[ROOT2]);
//	if (dist[ROOT1] < 0 && dist[ROOT2] > 0)
//		dist[RES] = dist[ROOT2];
//	else if (dist[ROOT1] > 0 && dist[ROOT2] > 0)
//		dist[RES] = dist[ROOT1];
//	else
//	{
//		dist[ROOT1] = 0;
//		dist[ROOT2] = 0;
//		dist[RES] = INFINITY;
//	}
//}
//
//int	intersect_cylinder(t_ray ray, t_stdobj *obj, float *dist)
//{
//	float	qd[7];
//	t_cy	*cyl;
//
//	cyl = (t_cy *)obj->obj;
//	qd[A] = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
//	qd[B] = 2 * ray.dir.x * (ray.origin.x - cyl->pos.x)
//		+ 2 * ray.dir.z * (ray.origin.z - cyl->pos.z);
//	qd[C] = (ray.origin.x - cyl->pos.x) * (ray.origin.x - cyl->pos.x)
//		+ (ray.origin.z - cyl->pos.z) * (ray.origin.z - cyl->pos.z)
//		- (cyl->diameter / 2) * (cyl->diameter / 2);
//	qd[DELTA] = (qd[B] * qd[B]) - (4 * qd[A] * qd[C]);
//	if (qd[DELTA] > 0)
//	{
//		qd[ROOT1] = (((-1 * qd[B] - sqrtf(qd[DELTA]))) / (2 * qd[A]));
//		qd[ROOT2] = (((-1 * qd[B] + sqrtf(qd[DELTA]))) / (2 * qd[A]));
//		check_for_solutions_cylinder(qd);
//		*dist = qd[RES];
//		return (1);
//	}
//	return (0);
//}

/*	quad 0  = ra
 * 	quad 1 = ab2
 * 	quad 2 = a
 * 	quad 3 = b
 * 	quad 4 = c
 * 	quad 5 = d
 * 	quad 6 = time
 *
 * 	v0 = A
 * 	v1 = B
 * 	v2 = AB
 * 	v3 = AO
 * 	v4 = AOxAB
 * 	v5 = VxAB
 * 	v6 = intersection
 * 	v7 = projection
 */

static void	init_quadra_cy(t_ray *ray, const t_cy *cyl, t_vec3 *v, float *quad)
{
	quad[0] = cyl->diameter / 2;
	v[0] = set_vec(cyl->pos.x, cyl->pos.y, cyl->pos.z + cyl->height / 2);
	v[1] = set_vec(cyl->pos.x, cyl->pos.y, cyl->pos.z - cyl->height / 2);
	v[2] = vec_sub(v[1], v[0]);
	v[3] = vec_sub((*ray).origin, v[0]);
	v[4] = vec_cross(v[3], v[2]);
	v[5] = vec_cross((*ray).dir, v[2]);
	quad[1] = vec_dot(v[2], v[2]);
	quad[2] = vec_dot(v[5], v[5]);
	quad[3] = 2 * vec_dot(v[5], v[4]);
	quad[4] = vec_dot(v[4], v[4]) - (quad[0] * quad[0] * quad[1]);
	quad[5] = quad[3] * quad[3] - 4 * quad[2] * quad[4];
}

int	intersect_cylinder(t_ray ray, t_stdobj *obj, float *dist)
{
	t_cy	*cyl;
	t_vec3	v[8];
	float	quad[7];

	cyl = (t_cy *)obj->obj;
	init_quadra_cy(&ray, cyl, v, quad);
	if (quad[5] < 0.0001f)
		return (0);
	quad[6] = (-quad[3] - sqrtf(quad[5])) / (2 * quad[2]);
	if (quad[6] < 0.0001f)
		return (0);
	v[6] = vec_add(ray.origin, vec_scale(ray.dir, quad[6]));
	v[7] = vec_add(v[0], vec_scale(v[2],
				vec_dot(v[2], vec_scale(vec_sub(v[6], v[0]), 1 / quad[1]))));
	if ((vec_length(vec_sub(v[7], v[0]))
			+ vec_length(vec_sub(v[1], v[7])) > vec_length(v[2])))
		return (0);
	*dist = quad[6];
	return (1);
}
