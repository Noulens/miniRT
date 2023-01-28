/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 05:59:59 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/23 18:31:01 by hyunah           ###   ########.fr       */
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
	if (d2 > powf(sphere->radius, 2))
		return (0);
	thc = sqrtf(powf(sphere->radius, 2) - d2);
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
 * I used this :
 * https://www.illusioncatalyst.com/notes.php
 *
 *	quad 0  = radius
 * 	quad 1 = 2ab
 * 	quad 2 = a
 * 	quad 3 = b
 * 	quad 4 = c
 * 	quad 5 = delta
 * 	quad 6 = time -> this is the return value that is the solution, hit distance
 *
 * 	v0 = A -> coordinate of extremities of obj adjusted with the orientation
 * 	v1 = B -> coordinate of extremities of obj adjusted with the orientation
 * 	v2 = AB -> segment from extremity A to B in the direction of obj
 * 	v3 = AO
 * 	v4 = AOxAB
 * 	v5 = VxAB
 * 	v6 = intersection
 * 	v7 = projection
 */

static void	init_quadra_cy(t_ray *ray, t_cy *cyl, t_vec3 *v, float *quad)
{
	quad[0] = cyl->diameter / 2;
	v[0] = vec_add(cyl->pos, vec_scale(cyl->orientation, cyl->height));
	v[1] = cyl->pos;
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
	t_cy		*cyl;
	t_inter_c	ic;
	t_pl		cap[2];
	t_stdobj	capper[2];

	cyl = (t_cy *)obj->obj;
	ic.dist = dist;
	ic.raycap = &ray;
	init_quadra_cy(&ray, cyl, ic.v, ic.quad);
	if (cyl->height == 0)
		return (isacap(cyl, &ic, cap, capper));
	if (ic.quad[5] < 10e-6)
		return (0);
	ic.quad[6] = (-ic.quad[3] - sqrtf(ic.quad[5])) / (2 * ic.quad[2]);
	if (ic.quad[6] < 10e-6)
		return (isacap(cyl, &ic, cap, capper));
	get_inter_proj(&ray, ic.v, ic.quad);
	if ((vec_length(vec_sub(ic.v[7], ic.v[0])) > vec_length(ic.v[2]))
		|| (vec_length(vec_sub(ic.v[1], ic.v[7])) > vec_length(ic.v[2])))
		return (isacap(cyl, &ic, cap, capper));
	*dist = ic.quad[6];
	return (1);
}

void	init_diskcone(t_co *cyl, t_vec3 v, t_pl *cap, t_stdobj *capper)
{
	cap->pos = v;
	cap->orientation = cyl->orientation;
	capper->obj = (void *)cap;
}

int	intersect_cone(t_ray ray, t_stdobj *obj, float *dist)
{
	t_co *cyl;
	t_inter_c ic;
	t_pl cap;
	t_stdobj capper;

	cyl = (t_co *) obj->obj;
	ic.raycap = &ray;
	ic.dist = dist;
	t_vec3 tip = vec_add(cyl->pos, vec_scale(cyl->orientation, cyl->height));
	t_vec3 bottom = cyl->pos;
	t_vec3 h = vec_sub(bottom, tip);
	float length = vec_length(h);
	float m = (cyl->rad * cyl->rad) / (length * length);
	t_vec3 w = vec_sub(ray.origin, tip);
	t_vec3 hh = vec_scale(h, 1 / length);
	float a = vec_dot(ray.dir, ray.dir) - m * vec_dot(ray.dir, hh) * vec_dot(ray.dir, hh) - vec_dot(ray.dir, hh) * vec_dot(ray.dir, hh);
	float b = 2 * (vec_dot(ray.dir, w) - m * vec_dot(ray.dir, hh) * vec_dot(w, hh) -
			vec_dot(ray.dir, hh) * vec_dot(w, hh));
	float c = vec_dot(w,w) - m * vec_dot(w, hh) * vec_dot(w, hh) - vec_dot(w, hh) * vec_dot(w, hh);
	float d = b * b - 4.0f * a * c;
	if (d < 10e-6)
		return (0);
	float sq = sqrtf(d);
	float t0 = (- b + sq) / ( 2.0f * a);
	float t1 = (- b - sq) / ( 2.0f * a);
	float tc;
	if (t0 > t1)
		tc = t1;
	else
	{
		tc = t0;
	}
	if (tc < 10e-6)
	{
		float	hit_dist;
		init_diskcone(cyl, bottom, &cap, &capper);
		hit_dist = INFINITY;
		if (intersect_plane(*ic.raycap, &capper, ic.dist))
		{
			if (getdouble(ic.raycap, ic.dist, cap)
				<= cyl->rad * cyl->rad)
				hit_dist = *ic.dist;
		}
		if (hit_dist != INFINITY)
		{
			return (hit_dist >= 0);
		}
		return (0);
	}
	if (tc > 10e-6)
	{
		t_vec3 hit_point = vec_add(ray.origin, vec_scale(ray.dir, tc));
		float hit_test = vec_dot(vec_sub(hit_point, tip), hh);
//		if 0≤(Lint−H)⋅h^≤∥h∥
//		The intersection is on the cone surface.
		if ((hit_test >= 0 && hit_test < length))
		{
			*dist = tc;
			return (tc >= 0);
		}
//		if (Lint−H)⋅h^>∥h∥
//		The intersection is below the base of the cone. Test the intersection with the cone base cap.
		if (hit_test > length)
		{
			float	hit_dist;
			init_diskcone(cyl, bottom, &cap, &capper);
			hit_dist = INFINITY;
			if (intersect_plane(*ic.raycap, &capper, ic.dist))
			{
				if (getdouble(ic.raycap, ic.dist, cap)
					<= cyl->rad * cyl->rad)
					hit_dist = *ic.dist;
			}
			if (hit_dist != INFINITY)
			{
				return (hit_dist >= 0);
			}
			return (0);
		}
	}
	return (0);
}
