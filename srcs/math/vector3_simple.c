/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 07:16:47 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/31 09:40:08 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

t_vec3	set_vec(float x, float y, float z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.t = 1;
	return (new);
}

int	vec_compt(t_vec3 a, t_vec3 b, int precision)
{
	int	x_same;
	int	y_same;
	int	z_same;

	x_same = 0;
	y_same = 0;
	z_same = 0;
	a = vec_scale(a, pow(10, precision));
	b = vec_scale(b, pow(10, precision));
	if (roundf(a.x) == roundf(b.x))
		x_same = 1;
	if (roundf(a.y) == roundf(b.y))
		y_same = 1;
	if (roundf(a.z) == roundf(b.z))
		z_same = 1;
	if (x_same && y_same && z_same)
		return (1);
	return (0);
}

t_vec3	set_vec_point_dir(t_vec3 point, t_vec3 dir, float t)
{
	t_vec3	v;
	t_vec3	orient;

	orient = vec_normalize(dir);
	v.x = point.x + (t * orient.x);
	v.y = point.y + (t * orient.y);
	v.z = point.z + (t * orient.z);
	return (v);
}
