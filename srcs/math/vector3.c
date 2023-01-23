/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 05:58:45 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/23 14:23:21 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"
#include <stdio.h>

float	vec_dot(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

float	vec_length(t_vec3 a)
{
	float	b;

	b = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
	return (sqrtf(b));
}

t_vec3	vec_normalize(t_vec3 vec)
{
	float	len;

	len = vec_length(vec);
	if (len == 0)
		return (ft_printf("Error\nvec length is 0\n"), set_vec(0, 0, 0));
	return (set_vec(vec.x * 1 / len, vec.y * 1 / len, vec.z * 1 / len));
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (set_vec(a.y * b.z - a.z * b.y, \
					a.z * b.x - a.x * b.z, \
					a.x * b.y - a.y * b.x));
}

int	cannot_norm(float x, float y, float z)
{
	if (!x && !y && !z)
	{
		ft_fprintf(2, "Error\nnull vector\n");
		return (TRUE);
	}
	return (FALSE);
}

//TODO : remove this printf:
void	print_vec(t_vec3 *a)
{
	printf("x = %f, y = %f, z = %f\n", a->x, a->y, a->z);
}
