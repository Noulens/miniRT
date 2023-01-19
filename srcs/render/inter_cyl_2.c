/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cyl_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:09:56 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/19 17:09:58 by tnoulens         ###   ########.fr       */
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
