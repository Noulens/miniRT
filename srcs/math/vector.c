/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 05:58:45 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/19 17:38:08 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"
#include <stdio.h>

double	vec_dot(t_vec a, t_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double	vec_length(t_vec a)
{
	double	b;

	b = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
	return (sqrt(b));
}

t_vec	vec_normalize(t_vec vec)
{
	double	len;

	len = vec_length(vec);
	if (len == 0)
		return (printf("Error : vec length is 0\n"), set_vec(0, 0, 0));
	return (set_vec(vec.x * 1 / len, vec.y * 1 / len, vec.z * 1 / len));
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	return (set_vec(a.y * b.z - a.z * b.y, \
					a.z * b.x - a.x * b.z, \
					a.x * b.y - a.y * b.x));
}
