/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 07:16:47 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/20 15:33:18 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

t_vec3	set_vec(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return (set_vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return (set_vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec_mult(t_vec3 a, double scale)
{	
	return (set_vec(a.x * scale, a.y * scale, a.z * scale));
}