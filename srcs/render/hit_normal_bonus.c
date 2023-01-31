/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_normal_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:53:27 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/31 11:28:35 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_vec3	get_len_texture(t_pl *pl, t_vec3 a, t_vec3 b, t_vec3 hit)
{
	t_ray	ray1;
	t_ray	ray2;
	t_vec3	intersect_point;
	t_vec3	point;

	point = set_vec(0, 0, 0);
	ray1.origin = set_vec_point_dir(point, vec_normalize(a), 1.00);
	ray1.dir = set_vec_point_dir(point, vec_normalize(a), 2.00);
	point = vec_sub(hit, pl->translate);
	ray2.origin = set_vec_point_dir(point, vec_normalize(b), 1.00);
	ray2.dir = set_vec_point_dir(point, vec_normalize(b), 2.00);
	if (query_intersection(ray1, ray2, &intersect_point))
		return (intersect_point);
	return (set_vec(0, 0, 0));
}

t_vec3	calcule_uv_point_plane(t_pl *pl, t_surfaceinfo *info)
{
	t_vec3	null;
	t_vec3	u_point;
	t_vec3	v_point;

	null = set_vec(0.0, 0.0, 0.0);
	if (vec_compt(pl->u_axis, set_vec(INFINITY, INFINITY, INFINITY), 1))
	{
		pl->u_axis = from_two_vec_do_rotation(set_vec(0, 1, 0), \
		pl->orientation, set_vec(1, 0, 0));
		matrix_vec_mult(set_transform2(&null, &pl->rotate), &pl->u_axis);
		pl->v_axis = from_two_vec_do_rotation(set_vec(0, 1, 0), \
		pl->orientation, set_vec(0, 0, 1));
		matrix_vec_mult(set_transform2(&null, &pl->rotate), &pl->v_axis);
	}
	u_point = get_len_texture(pl, pl->u_axis, pl->v_axis, info->hit_point);
	v_point = get_len_texture(pl, pl->v_axis, pl->u_axis, info->hit_point);
	if (vec_dot((u_point), (pl->u_axis)) < 0)
		info->hit_uv.y = -1 * vec_length(v_point);
	else
		info->hit_uv.y = vec_length(v_point);
	if (vec_dot((v_point), (pl->v_axis)) < 0)
		info->hit_uv.x = -1 * vec_length(u_point);
	else
		info->hit_uv.x = vec_length(u_point);
	return (info->hit_uv);
}
