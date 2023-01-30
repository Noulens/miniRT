/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cyl_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:09:56 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/30 23:50:16 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	init_disk(t_cy *cyl, t_vec3 *v, t_pl *cap, t_stdobj *capper)
{
	cap[0].pos = v[0];
	cap[0].orientation = cyl->orientation;
	cap[1].pos = v[1];
	cap[1].orientation = cyl->orientation;
	capper[0].obj = (void *)&cap[0];
	capper[1].obj = (void *)&cap[1];
}

float	getdouble(t_ray *ray, const float *dist, const t_pl cap)
{
	t_vec3	p;
	t_vec3	vec;
	float	d2;

	p = vec_add((*ray).origin, vec_scale((*ray).dir, *dist));
	vec = vec_sub(p, cap.pos);
	d2 = vec_dot(vec, vec);
	return (d2);
}

void	get_inter_proj(t_ray *ray, t_vec3 *v, const float *quad)
{
	v[6] = vec_add((*ray).origin, vec_scale((*ray).dir, quad[6]));
	v[7] = vec_add(v[0], vec_scale(v[2],
				vec_dot(v[2], vec_scale(vec_sub(v[6], v[0]), 1 / quad[1]))));
}

void	check_hitdistance(t_inter_c *ic, const float *hit_dist)
{
	if (hit_dist[0] > hit_dist[1])
		*ic->dist = hit_dist[1];
	else
		*ic->dist = hit_dist[0];
}

int	isacap(t_cy *cyl, t_inter_c *ic, t_pl *cap, t_stdobj *capper)
{
	int		k;
	float	hit_dist[2];

	init_disk(cyl, ic->v, cap, capper);
	hit_dist[0] = INFINITY;
	hit_dist[1] = INFINITY;
	k = -1;
	while (++k < 2)
	{
		if (intersect_plane(*ic->raycap, &capper[k], ic->dist))
		{
			if (getdouble(ic->raycap, ic->dist, cap[k])
				<= ic->quad[0] * ic->quad[0])
				hit_dist[k] = *ic->dist;
		}
	}
	if (hit_dist[0] != INFINITY || hit_dist[1] != INFINITY)
	{
		check_hitdistance(ic, hit_dist);
		return (1);
	}
	return (0);
}
