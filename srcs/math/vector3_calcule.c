/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_calcule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:32:48 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/31 09:39:23 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return (set_vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return (set_vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec_mult(t_vec3 a, t_vec3 b)
{
	return (set_vec(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	vec_scale(t_vec3 a, float b)
{
	return (set_vec(a.x * b, a.y * b, a.z * b));
}
