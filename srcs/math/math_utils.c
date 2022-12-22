/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:38:33 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/21 15:02:33 by waxxy            ###   ########.fr       */
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