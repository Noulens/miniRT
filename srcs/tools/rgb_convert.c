/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:55:54 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/13 13:55:59 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "math_func.h"

t_vec3	vec_color(int color)
{
	float	r;
	float	g;
	float	b;

	r = ft_remap(get_r(color), 0, 255, 0, 1);
	g = ft_remap(get_g(color), 0, 255, 0, 1);
	b = ft_remap(get_b(color), 0, 255, 0, 1);
	return (set_vec(r, g, b));
}

int	int_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)ft_remap(color.x, 0, 1, 0, 255);
	g = (int)ft_remap(color.y, 0, 1, 0, 255);
	b = (int)ft_remap(color.z, 0, 1, 0, 255);
	return (ft_trgb(255, r, g, b));
}