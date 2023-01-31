/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:56:01 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/31 11:24:00 by hyunah           ###   ########.fr       */
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

void	keep_between_zero_one(float *f)
{
	if (*f >= 1.0)
		*f = 1.0;
	if (*f <= 0)
		*f = 0.0;
}
