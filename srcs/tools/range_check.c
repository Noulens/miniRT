/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:32:29 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/13 15:14:10 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	rgb_range_checker(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = ft_atoi(line + i);
	if (r > 255 || r < 0)
		return (ft_fprintf(2, "Error\nin rgb data: r not in range\n"), 1);
	while (line[i] != ',')
		++i;
	g = ft_atoi(line + ++i);
	if (g > 255 || g < 0)
		return (ft_fprintf(2, "Error\nin rgb data: g not in range\n"), 1);
	while (line[i] != ',')
		++i;
	b = ft_atoi(line + ++i);
	if (b > 255 || b < 0)
		return (ft_fprintf(2, "Error\nin b data: b not in range\n"), 1);
	return (0);
}

int	float_range_checker(float val, float lower, float upper, int incl)
{
	if (incl == 0)
	{
		if (val > lower && val < upper)
			return (TRUE);
	}
	else if (incl == 1)
	{
		if (val >= lower && val <= upper)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}

void	ft_swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

float	ft_max(float a, float b)
{
	if (a <= b)
		return (b);
	return (a);
}
