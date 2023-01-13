/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:56:01 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/13 13:38:03 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "math_func.h"

int	ft_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xff);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xff);
}

int	get_b(int trgb)
{
	return (trgb & 0xff);
}

float	ft_remap(float v, float from_start, float from_end, float to_start, float to_end)
{
	return ((v * (to_end - to_start) / (from_end - from_start)));
}

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