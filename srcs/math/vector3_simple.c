/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 07:16:47 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/21 15:03:20 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

t_vec3	set_vec(float x, float y, float z)
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

t_vec3	vec_mult(t_vec3 a, float scale)
{
	return (set_vec(a.x * scale, a.y * scale, a.z * scale));
}
