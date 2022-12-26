/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:32:29 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/23 12:25:51 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	rgb_range_checker(char *line)
{
	int i;
	int r;
	int g;
	int b;

	i = 0;
	while (line[i] == ' ')
		++i;
	r = ft_atoi(line + i);
	if (r > 255 || r < 0)
		return (ft_fprintf(2, "Error in rgb data: r not in range"), 1);
	while (line[i] != ',')
		++i;
	g = ft_atoi(line + ++i);
	if (g > 255 || g < 0)
		return (ft_fprintf(2, "Error in rgb data: g not in range"), 1);
	while (line[i] != ',')
		++i;
	b = ft_atoi(line + ++i);
	if (b > 255 || b < 0)
		return (ft_fprintf(2, "Error in b data: b not in range"), 1);
	return (0);
}

int int_range_checker(int val, int lower, int upper, int include)
{
	if (include == 0)
	{
		if (val > lower && val < upper)
			return (TRUE);

	}
	else if (include == 1)
	{
		if (val >= lower && val <= upper)
			return (TRUE);
	}
	return (FALSE);
}

int	float_range_checker(float val, float lower, float upper, int include)
{
	if (include == 0)
	{
		if (val > lower && val < upper)
			return (TRUE);
	}
	else if (include == 1)
	{
		if (val >= lower && val <= upper)
		{
			return (TRUE);
		}
	}
	return (FALSE);
}
