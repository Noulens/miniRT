/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 05:59:59 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/12 07:49:59 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	intersect_sphere(t_ray ray, t_stdobj *tmp, float *hit_distance)
{
	float		t0;
	float		t1;
	float		tca;
	float		thc;
	float		d2;
	float		sphere_radius;
	t_vec3		sphere_pos;
	t_vec3		l;
	t_sp		*sphere;

	sphere = (t_sp *)tmp->obj;
	sphere_radius = sphere->diameter / 2.0f;
	sphere_pos = sphere->pos;
	// printf("2center : %f, %f, %f\n", sphere->pos.x, sphere->pos.y,  sphere->pos.z);
	l = vec_sub(sphere_pos, ray.origin);
	tca = vec_dot(l, ray.dir);
	if (tca < 0)
		return (0);
	d2 = vec_dot(l, l) - tca * tca;
	if (d2 > sphere_radius)
		return (0);
	thc = sqrtf(sphere_radius - d2);
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
static void	check_for_solutions_cylinder(float *dist)
{
	if (dist[0] > dist[1])
		ft_swap(&dist[0], &dist[1]);
	if (dist[0] < 0 && dist[1] > 0)
		dist[2] = dist[1];
	else if (dist[0] > 0 && dist[1] > 0)
		dist[2] = dist[0];
	else
	{
		dist[0] = 0;
		dist[1] = 0;
		dist[2] = INFINITY;
	}
}

int	intersect_cylinder(t_ray ray, t_stdobj *obj, float *dist)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	root[3];
	t_cy	*cylinder;

	cylinder = (t_cy *)obj->obj;
	a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	b = 2 * ray.dir.x * (ray.origin.x - cylinder->pos.x) +
		2 * ray.dir.z * (ray.origin.z - cylinder->pos.z);
	c = (ray.origin.x -  cylinder->pos.x) * (ray.origin.x - cylinder->pos.x) +
		(ray.origin.z - cylinder->pos.z) * (ray.origin.z - cylinder->pos.z) -
		(cylinder->diameter / 2) * (cylinder->diameter / 2);
	delta = (b * b) - (4 * a * c);
	if (delta > 0)
	{
		root[0] = (((-1 * b - sqrtf(delta))) / (2 * a));
		root[1] = (((-1 * b + sqrtf(delta))) / (2 * a));
		check_for_solutions_cylinder(root);
		*dist = root[2];
		return (1);
	}
	return (0);
}
