/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 07:16:47 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/19 11:45:08 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

t_vec	set_vec(double x, double y, double z)
{
	t_vec	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	return (set_vec(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	return (set_vec(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec	vec_mult(t_vec a, double scale)
{	
	return (set_vec(a.x * scale, a.y * scale, a.z * scale));
}
