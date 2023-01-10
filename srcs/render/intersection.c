/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 05:59:59 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/10 06:05:07 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	ft_swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

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
	return 0;
}
/*
int intersect_cylinder(t_ray ray, t_stdobj *cy_std, float *hit_distance)
{
	double a;
	double b;
	double c;
	double delta;
	double root;
	t_cy	*cylinder;

	cylinder = (t_cy *)cy_std;
	a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	b = 2 * ray.dir.x * (ray.origin.x - cylinder->pos.x) +
		2 * ray->dir->z * (ray->ori->z - cylinder->base->z);
	c = (ray->ori->x - cylinder->base->x) * (ray->ori->x - cylinder->base->x) +
		(ray->ori->z - cylinder->base->z) * (ray->ori->z - cylinder->base->z) -
		cylinder->radius * cylinder->radius;
	delta = b * b - (4 * a * c);
	if (delta > ACC)
	{
		root = (-1 * b - sqrt(delta)) / (2 * a) - ACC;
		if (root <= ACC)
			root = (-1 * b + sqrt(delta)) / (2 *a) - ACC;
		return (root);
	}
	return (-1);
}
*/
