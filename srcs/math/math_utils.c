/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:38:33 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/20 17:57:54 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

double	to_radian(double degree)
{
	return (degree * M_PI / 180);
}

double	to_degree(double radian)
{
	return (radian * 180 / M_PI);
}