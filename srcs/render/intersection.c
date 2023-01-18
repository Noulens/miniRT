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
/*
int intersect_cylinder(t_ray ray, t_stdobj *cy_std, float *hit_distance)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	root;
	t_cy	*cylinder;

	cylinder = (t_cy *)cy_std;
	a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	b = 2 * ray.dir.x * (ray.origin.x - cylinder->pos.x) +
		2 * ray.dir.z * (ray.origin.z - cylinder->pos.z);
	c = (ray.origin.x -  cylinder->pos.x) * (ray.origin.x - cylinder->pos.x) +
		(ray.origin.z - cylinder->pos.z) * (ray.origin.z - cylinder->pos.z) -
			(cylinder->diameter / 2) * (cylinder->diameter / 2);
	delta = b * b - (4 * a * c);
	if (delta > 0)
	{
		root = (-b - sqrtf(delta)) / (2 * a);
		if (root <= 0)
			root = (-b + sqrtf(delta)) / (2 *a);
		*hit_distance = root;
		return (1);
	}
	return (0);
}
*/

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

int	intersect_cylinder(t_ray ray, t_stdobj *obj, float *dist)
{
	t_cy	*cyl;
	t_vec3	A;
	t_vec3	B;

	cyl = (t_cy *)obj->obj;

	float ra = cyl->diameter / 2;
	A = set_vec(cyl->pos.x, cyl->pos.y, cyl->pos.z + cyl->height / 2);
	B = set_vec(cyl->pos.x, cyl->pos.y, cyl->pos.z - cyl->height / 2);
	t_vec3 AB = vec_sub(B, A);
	t_vec3 AO = vec_sub(ray.origin, A);
	t_vec3 AOxAB = vec_cross(AO,AB);
	t_vec3 VxAB = vec_cross(ray.dir, AB);
	float ab2 = vec_dot(AB, AB);
	float a = vec_dot(VxAB,VxAB);
	float b = 2 * vec_dot(VxAB, AOxAB);
	float c = vec_dot(AOxAB, AOxAB) - (ra * ra * ab2);
	float d = b * b - 4 * a * c;
	if (d < 0.0f)
		return (0);
	float time = (-b - sqrtf(d)) / (2 * a);
	if (time < 0.0f)
		return (0);
	t_vec3 intersection = vec_add(ray.origin, vec_scale(ray.dir, time));
	t_vec3 projection = vec_add(A, vec_scale(AB, vec_dot(AB, vec_scale(vec_sub(intersection, A), 1 / ab2))));
	if ((vec_length(vec_sub(projection, A)) + vec_length(vec_sub(B, projection)) < vec_length(AB))
		|| (vec_length(vec_sub(projection, A)) + vec_length(vec_sub(B, projection)) > vec_length(AB)))
	{
		*dist = time;
//		(void)dist;
		return (1);
	}
	return (0);
}
