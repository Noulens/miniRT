/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_co_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:05:01 by tnoulens          #+#    #+#             */
/*   Updated: 2023/02/02 18:20:48 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/*
 * I used this :
 * https://www.illusioncatalyst.com/notes.php
 *
 *	quad 0  = length of cone
 * 	quad 1 = r * r / lenght * lenght
 * 	quad 2 = a
 * 	quad 3 = b
 * 	quad 4 = c
 * 	quad 5 = delta
 * 	quad 6 = time -> this is the return value that is the solution, hit distance
 * 	quad 7 = our test distance with the cap, if greater than quad 6 then its a
 * 	hit on the cone surface
 * 	quad 8 = (Lint−H)⋅h^ : if 0≤(Lint−H)⋅h^≤∥h∥ the intersection is on
 * 	the cone surface. Or, if (Lint−H)⋅h^>∥h∥ the intersection is below the
 * 	base of the cone. Test the intersection with the cone base cap.
 *
 * 	v0 = tip
 * 	v1 = bottom
 * 	v2 = segment from tip to bottom in the direction of obj
 * 	v3 = AO
 * 	v4 = AOxAB
 * 	v5 = point of intersection between ray and cone
 */

static void	init_diskcone(t_co *cyl, t_vec3 v, t_pl *cap, t_stdobj *capper)
{
	cap->pos = v;
	cap->orientation = cyl->orientation;
	capper->obj = (void *)cap;
}

static float	init_quadra_co(float*dist, t_co*cyl, t_ray*ray, t_inter_c*ic)
{
	(*ic).raycap = ray;
	(*ic).dist = dist;
	(*ic).v[0] = vec_add(cyl->pos, vec_scale(cyl->orientation, cyl->height));
	(*ic).v[2] = vec_sub(cyl->pos, (*ic).v[0]);
	(*ic).quad[0] = vec_length((*ic).v[2]);
	(*ic).quad[1] = (cyl->rad * cyl->rad) / ((*ic).quad[0] * (*ic).quad[0]);
	(*ic).v[3] = vec_sub((*ray).origin, (*ic).v[0]);
	(*ic).v[4] = vec_scale((*ic).v[2], 1 / (*ic).quad[0]);
	(*ic).quad[2] = vec_dot((*ray).dir, (*ray).dir) - (*ic).quad[1] \
	* vec_dot((*ray).dir, (*ic).v[4]) * vec_dot((*ray).dir, (*ic).v[4]) \
	- vec_dot((*ray).dir, (*ic).v[4]) * vec_dot((*ray).dir, (*ic).v[4]);
	(*ic).quad[3] = 2 * (vec_dot((*ray).dir, (*ic).v[3]) - (*ic).quad[1] \
	* vec_dot((*ray).dir, (*ic).v[4]) * vec_dot((*ic).v[3], (*ic).v[4]) \
	- vec_dot((*ray).dir, (*ic).v[4]) * vec_dot((*ic).v[3], (*ic).v[4]));
	(*ic).quad[4] = vec_dot((*ic).v[3], (*ic).v[3]) - (*ic).quad[1] \
	* vec_dot((*ic).v[3], (*ic).v[4]) * vec_dot((*ic).v[3], (*ic).v[4]) \
	- vec_dot((*ic).v[3], (*ic).v[4]) * vec_dot((*ic).v[3], (*ic).v[4]);
	(*ic).quad[5] = (*ic).quad[3] * (*ic).quad[3] - 4.0f \
	* (*ic).quad[2] * (*ic).quad[4];
	return ((*ic).quad[5]);
}

static void	captst(const t_co *cyl, t_pl *cap, t_inter_c *ic, t_stdobj *capper)
{
	(*ic).quad[7] = INFINITY;
	if (intersect_plane(*(*ic).raycap, capper, (*ic).dist))
	{
		if (getdouble((*ic).raycap, (*ic).dist, (*cap)) <= cyl->rad * cyl->rad)
			(*ic).quad[7] = *(*ic).dist;
	}
	(*ic).quad[6] = (- (*ic).quad[3] - sqrtf((*ic).quad[5])) \
	/ (2.0f * (*ic).quad[2]);
	if ((*ic).quad[6] < 10e-6)
		(*ic).quad[6] = (- (*ic).quad[3] + sqrtf((*ic).quad[5])) \
		/ (2.0f * (*ic).quad[2]);
	(*ic).v[5] = vec_add(ic->raycap->origin, \
	vec_scale(ic->raycap->dir, (*ic).quad[6]));
	(*ic).quad[8] = vec_dot(vec_sub((*ic).v[5], (*ic).v[0]), (*ic).v[4]);
}

int	intersect_cone(t_ray ray, t_stdobj *obj, float *dist)
{
	t_co		*cyl;
	t_inter_c	ic;
	t_pl		cap;
	t_stdobj	capper;

	cyl = (t_co *) obj->obj;
	if (init_quadra_co(dist, cyl, &ray, &ic) < 10e-6)
		return (0);
	init_diskcone(cyl, cyl->pos, &cap, &capper);
	captst(cyl, &cap, &ic, &capper);
	if (ic.quad[6] >= 10e-6)
	{
		if (ic.quad[7] < ic.quad[6])
			return (1);
		if ((ic.quad[8] >= 0 && ic.quad[8] <= ic.quad[0]))
			return (*dist = ic.quad[6], 1);
		if (ic.quad[8] > ic.quad[0])
		{
			init_diskcone(cyl, cyl->pos, &cap, &capper);
			if (intersect_plane(*ic.raycap, &capper, ic.dist))
				if (getdouble(ic.raycap, ic.dist, cap) <= cyl->rad * cyl->rad)
					return (1);
		}
	}
	return (0);
}
