/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:18:35 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/23 13:50:19 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

void	set_identity(t_matrix4 *matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				matrix->m[i][j] = 1.0f;
			else
				matrix->m[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	set_transmat(const t_vec3 *trans, t_matrix4 *t)
{
	t[T].m[0][3] = trans->x;
	t[T].m[1][3] = trans->y;
	t[T].m[2][3] = trans->z;
}

static void	set_rotmat(const t_vec3 *rot, t_matrix4 *t)
{
	t[RZ].m[0][0] = cosf(to_radian(rot->z));
	t[RZ].m[0][1] = -sinf(to_radian(rot->z));
	t[RZ].m[1][0] = sinf(to_radian(rot->z));
	t[RZ].m[1][1] = cosf(to_radian(rot->z));
	t[RY].m[0][0] = cosf(to_radian(rot->y));
	t[RY].m[0][2] = sinf(to_radian(rot->y));
	t[RY].m[2][0] = -sinf(to_radian(rot->y));
	t[RY].m[2][2] = cosf(to_radian(rot->y));
	t[RX].m[1][1] = cosf(to_radian(rot->x));
	t[RX].m[1][2] = -sinf(to_radian(rot->x));
	t[RX].m[2][1] = sinf(to_radian(rot->x));
	t[RX].m[2][2] = cosf(to_radian(rot->x));
}

void	set_transform(t_vec3 *trans, t_vec3 *rot, t_scene *s)
{
	t_matrix4	t[4];
	int			i;

	i = -1;
	while (++i < 4)
		set_identity(&t[i]);
	set_transmat(trans, t);
	set_rotmat(rot, t);
	s->fwtfm = mul_mat(mul_mat(mul_mat(t[T], t[RX]), t[RY]), t[RZ]);
}

t_matrix4	mul_mat(t_matrix4 mat1, t_matrix4 mat2)
{
	float		res;
	int			c;
	int			d;
	int			k;
	t_matrix4	ret;

	c = -1;
	while (++c < 4)
	{
		d = -1;
		while (++d < 4)
		{
			k = -1;
			while (++k < 4)
				res = res + mat1.m[c][k] * mat2.m[k][d];
			ret.m[c][d] = res;
			res = 0;
		}
	}
	return (ret);
}
