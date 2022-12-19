/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:48:59 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/19 11:21:23 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_FUNC_H
# define MATH_FUNC_H
# include "math.h"

typedef struct s_vec{
	double	x;
	double	y;
	double	z;
}	t_vec;


typedef struct s_matrix4{
	double	m[4][4];
}	t_matrix4;


t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mult(t_vec a, double scale);
t_vec	set_vec(double x, double y, double z);
double	vec_length(t_vec a);
double	vec_dot(t_vec a, t_vec b);
t_vec	vec_cross(t_vec a, t_vec b);
t_vec	vec_normalize(t_vec vec);

#endif
