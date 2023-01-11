/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 07:23:37 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/23 16:43:49 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"
#include <stdio.h>

t_matrix4	init_matrix(t_matrix4 *new)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			new->m[i][j] = 0;
	}
	return (*new);
}

void	matrix_print(t_matrix4 n, int dir_flag)
{
	(void)dir_flag;
	printf("--------matrix---------\n");
	printf("%f %f %f %f\n", n.m[0][0], \
	n.m[0][1], n.m[0][2], n.m[0][3]);
	printf("%f %f %f %f\n", n.m[1][0], \
	n.m[1][1], n.m[1][2], n.m[1][3]);
	printf("%f %f %f %f\n", n.m[2][0], \
	n.m[2][1], n.m[2][2], n.m[2][3]);
	printf("%f %f %f %f\n", n.m[3][0], \
	n.m[3][1], n.m[3][2], n.m[3][3]);
	printf("----------------------\n");
}

void	matrix_vec_mult(t_matrix4 new, t_vec3 *vect)
{
	t_vec3	tmp;

	tmp = set_vec(vect->x, vect->y, vect->z);
	vect->x = new.m[0][0] * tmp.x + new.m[0][1] * tmp.y + new.m[0][2] * tmp.z
		+ new.m[0][3] * tmp.t;
	vect->y = new.m[1][0] * tmp.x + new.m[1][1] * tmp.y + new.m[1][2] * tmp.z
		+ new.m[1][3] * tmp.t;
	vect->z = new.m[2][0] * tmp.x + new.m[2][1] * tmp.y + new.m[2][2] * tmp.z
		+ new.m[2][3] * tmp.t;
}

/*
t_matrix4	matrix_transformation(t_vec3 *src, t_vec3 t, t_vec3 r)
{
	t_matrix4	transform;
	// calculation order to be tested.
	// UPDATE : it doesn't work. Feel free to rewrite.
	init_matrix(&transform);
	transform.m[0][0] = cosf(to_radian(r.y)) * cosf(to_radian(r.z));
	transform.m[0][1] = sinf(to_radian(r.x)) * sinf(to_radian(r.y)) * \
	cosf(to_radian(r.z)) - cosf(to_radian(r.x)) * sinf(to_radian(r.z));
	transform.m[0][2] = cosf(to_radian(r.x)) * sinf(to_radian(r.y)) * \
	cosf(to_radian(r.z)) + sinf(to_radian(r.x)) * sinf((r.z));
	transform.m[0][3] = t.x;
	transform.m[1][0] = cosf(to_radian(r.y)) * sinf(to_radian(r.z));
	transform.m[1][1] = sinf(to_radian(r.x)) * sinf(to_radian(r.y)) * \
	sinf(to_radian(r.z)) + cosf(to_radian(r.x)) * cosf(to_radian(r.z));
	transform.m[1][2] = cosf(to_radian(r.x)) * sinf(to_radian(r.y)) * \
	sinf(to_radian(r.z)) - sinf(to_radian(r.x)) * cosf(to_radian(r.z));
	transform.m[1][3] = t.y;
	transform.m[2][0] = -sinf(to_radian(r.y));
	transform.m[2][1] = sinf(to_radian(r.x)) * cosf(to_radian(r.y));
	transform.m[2][2] = cosf(to_radian(r.x)) * cosf(to_radian(r.y));
	transform.m[2][3] = t.z;
	matrix_vec_mult(transform, src);
	return (transform);
}
*/

/*
t_ray	trsfrm_ray(t_ray *ray, int dir_flag)
{
	t_ray	transformed_ray;

	(void)ray;
	(void)dir_flag;
	transformed_ray = *ray;
	return (transformed_ray);
}

t_vec3	trsfrm_vec(t_vec3 *vec, int dir_flag)
{
	t_vec3	transformed_vec;

	(void)vec;
	(void)dir_flag;
	transformed_vec = set_vec(1, 1, 1);
	return (transformed_vec);
}
 */
