/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:48:59 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/21 15:02:40 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_FUNC_H
# define MATH_FUNC_H
# include "math.h"

typedef struct s_vec3{
	float	x;
	float	y;
	float	z;
}	t_vec3;


typedef struct s_matrix4{
	float	m[4][4];
}	t_matrix4;

t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_mult(t_vec3 a, float scale);
t_vec3		set_vec(float x, float y, float z);
float		vec_length(t_vec3 a);
float		vec_dot(t_vec3 a, t_vec3 b);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
t_vec3		vec_normalize(t_vec3 vec);
t_matrix4	set_matrix(t_vec3 t, t_vec3 r, t_vec3 s);
void		matrix_print(t_matrix4 n);
void		matrix_vec_mult(t_matrix4 new, t_vec3 *vector);
float		to_degree(float radian);
float		to_radian(float degree);
t_matrix4	init_matrix(t_matrix4 *new);
t_matrix4	matrix_transformation(t_vec3 *src, t_vec3 t, t_vec3 r);
t_matrix4	matrix_rotateX(float x);
t_matrix4	matrix_rotateY(float y);
t_matrix4	matrix_rotateZ(float z);
t_matrix4	matrix_scale(t_vec3 s);
t_matrix4	matrix_translate(t_vec3 t);

#endif
