/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 05:58:45 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/30 14:59:45 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

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
		return (set_vec(0, 0, 0));
	return (set_vec(vec.x * 1 / len, vec.y * 1 / len, vec.z * 1 / len));
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (set_vec(a.y * b.z - a.z * b.y, \
					a.z * b.x - a.x * b.z, \
					a.x * b.y - a.y * b.x));
}

void	print_vec(t_vec3 *a)
{
	ft_printf("x = ");
	ft_putfloat_fd(a->x, 2, 1);
	ft_printf(" y = ");
	ft_putfloat_fd(a->y, 2, 1);
	ft_printf(" z = ");
	ft_putfloat_fd(a->z, 2, 1);
	ft_putchar_fd('\n', 1);
}
