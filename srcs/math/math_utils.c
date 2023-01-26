/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:38:33 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/13 15:17:06 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

float	to_radian(float degree)
{
	return (degree * M_PI / 180);
}

float	to_degree(float radian)
{
	return (radian * 180 / M_PI);
}

float	base_cylinder(float radius)
{
	return (M_PI * radius * radius);
}

float	ft_remap(float v, float fe, float te)
{
	return ((v * te / fe));
}

float	modulo(float x)
{
	return (x - floorf(x));
}
