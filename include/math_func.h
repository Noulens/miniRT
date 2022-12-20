/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:48:59 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/20 07:47:26 by hyunah           ###   ########.fr       */
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


t_vec		vec_add(t_vec a, t_vec b);
t_vec		vec_sub(t_vec a, t_vec b);
t_vec		vec_mult(t_vec a, double scale);
t_vec		set_vec(double x, double y, double z);
double		vec_length(t_vec a);
double		vec_dot(t_vec a, t_vec b);
t_vec		vec_cross(t_vec a, t_vec b);
t_vec		vec_normalize(t_vec vec);
t_matrix4	set_matrix(t_vec t, t_vec r, t_vec s);
void		matrix_print(t_matrix4 n);
void		matrix_vec_mult(t_matrix4 new, t_vec *vector);
double		to_radian(double degree);
t_matrix4	init_matrix(t_matrix4 *new);
t_matrix4	matrix_transformation(t_vec *src, t_vec t, t_vec r);
t_matrix4	matrix_rotateX(double x);
t_matrix4	matrix_rotateY(double y);
t_matrix4	matrix_rotateZ(double z);
t_matrix4	matrix_scale(t_vec s);
t_matrix4	matrix_translate(t_vec t);

#endif
