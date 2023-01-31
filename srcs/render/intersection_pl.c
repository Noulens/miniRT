/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_pl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:07:55 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/31 11:28:35 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	intersect_plane_new(t_ray ray, t_stdobj *tmp, float *hit_distance)
{
	t_pl	*plane;
	t_vec3	plane_n;
	t_vec3	intersect_pos;
	t_vec3	vec_null;
	float	dist_btw_cam_planeinter;

	vec_null = set_vec(0, 0, 0);
	plane = (t_pl *)tmp->obj;
	if (vec_compt(plane->hit_normal, set_vec(INFINITY, INFINITY, INFINITY), 1))
	{
		plane_n = set_vec(0, 1, 0);
		plane_n = from_two_vec_do_rotation(set_vec(0, 1, 0), \
		vec_normalize(plane->orientation), plane_n);
		matrix_vec_mult(set_transform2(&vec_null, &plane->rotate), &plane_n);
		plane->hit_normal = plane_n;
	}
	if (vec_dot(plane->hit_normal, ray.dir) != 0)
	{
		intersect_pos = vec_sub(plane->translate, ray.origin);
		dist_btw_cam_planeinter = vec_dot(intersect_pos, \
		plane->hit_normal) / vec_dot(plane->hit_normal, ray.dir);
		*hit_distance = dist_btw_cam_planeinter;
		return (dist_btw_cam_planeinter >= 0);
	}
	return (0);
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
