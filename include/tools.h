/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:44:04 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/22 22:58:18 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define FAIL 1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# include <math.h>

int ft_trgb(int t, int r, int g, int b);
int get_t(int trgb);
int get_r(int trgb);
int get_g(int trgb);
int get_b(int trgb);
int int_range_checker(int val, int lower, int upper, int include);
int float_range_checker(float val, float lower, float upper, int include);

#endif
