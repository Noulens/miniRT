/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 05:58:45 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/20 15:34:08 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"
#include <stdio.h>

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double	vec_length(t_vec3 a)
{
	double	b;

	b = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
	return (sqrt(b));
}

t_vec3	vec_normalize(t_vec3 vec)
{
	double	len;

	len = vec_length(vec);
	if (len == 0)
		return (printf("Error : vec length is 0\n"), set_vec(0, 0, 0));
	return (set_vec(vec.x * 1 / len, vec.y * 1 / len, vec.z * 1 / len));
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (set_vec(a.y * b.z - a.z * b.y, \
					a.z * b.x - a.x * b.z, \
					a.x * b.y - a.y * b.x));
}
