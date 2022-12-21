/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:32:29 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/21 19:03:05 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

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
			return (TRUE);
	}
	return (FALSE);
}
