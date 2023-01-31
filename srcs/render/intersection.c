/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 05:59:59 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/31 11:08:08 by hyunah           ###   ########.fr       */
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
