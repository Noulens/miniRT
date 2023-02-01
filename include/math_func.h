/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:48:59 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/31 15:09:59 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_FUNC_H
# define MATH_FUNC_H
# include "math.h"
# include "struct.h"
# include "libft.h"

# define FWDTFORM 1
# define BCKTFORM 0

t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_mult(t_vec3 a, t_vec3 b);
t_vec3		vec_scale(t_vec3 a, float b);
t_vec3		set_vec(float x, float y, float z);
float		vec_length(t_vec3 a);
float		vec_dot(t_vec3 a, t_vec3 b);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
t_vec3		vec_normalize(t_vec3 vec);
t_matrix4	set_matrix(t_vec3 t, t_vec3 r, t_vec3 s);
void		matrix_print(t_matrix4 n, int dir_flag);
void		matrix_vec_mult(t_matrix4 new, t_vec3 *vector);
float		to_degree(float radian);
float		to_radian(float degree);
t_matrix4	init_matrix(t_matrix4 *new);
void		set_transform(t_vec3 *trans, t_vec3 *rot, t_scene *s);
t_matrix4	matrix_transformation(t_vec3 *src, t_vec3 t, t_vec3 r);
void		print_vec(t_vec3 *a);
void		set_identity(t_matrix4 *matrix);
t_matrix4	mul_mat(t_matrix4 mat1, t_matrix4 mat2);
float		base_cylinder(float radius);
float		ft_max(float a, float b);
float		ft_remap(float v, float fe, float te);
t_matrix4	inverse(t_matrix4 t);
int			cannot_norm(float x, float y, float z);
float		modulo(float x);
t_vec3		rotate_from_axis_angle(t_vec3 vector, t_vec3 axis, float angle);
int			query_intersection(t_ray ray1, t_ray ray2, t_vec3 *intersect_point);
t_vec3		set_vec_point_dir(t_vec3 point, t_vec3 dir, float t);
int			vec_compt(t_vec3 a, t_vec3 b, int precision);
t_vec3		from_two_vec_do_rotation(t_vec3 origin1, t_vec3 target1, \
t_vec3 origin2);
t_matrix4	set_transform2(t_vec3 *trans, t_vec3 *rot);

#endif
