/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 07:23:37 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/31 15:40:17 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"
#include <stdio.h>

void	mtx_print_2(t_matrix4 *n)
{
	ft_putfloat_fd((*n).m[2][0], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd((*n).m[2][1], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd((*n).m[2][2], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd((*n).m[2][3], 2, 1);
	ft_putchar_fd('\n', 1);
	ft_putfloat_fd((*n).m[3][0], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd((*n).m[3][1], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd((*n).m[3][2], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd((*n).m[3][3], 2, 1);
	ft_putchar_fd('\n', 1);
}

void	matrix_print(t_matrix4 n, int dir_flag)
{
	(void)dir_flag;
	ft_printf("------matrix-------\n");
	ft_putfloat_fd(n.m[0][0], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd(n.m[0][1], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd(n.m[0][2], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd(n.m[0][3], 2, 1);
	ft_putchar_fd('\n', 1);
	ft_putfloat_fd(n.m[1][0], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd(n.m[1][1], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd(n.m[1][2], 2, 1);
	ft_putchar_fd(' ', 1);
	ft_putfloat_fd(n.m[1][3], 2, 1);
	ft_putchar_fd('\n', 1);
	mtx_print_2(&n);
	ft_printf("------------------\n");
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

int	cannot_norm(float x, float y, float z)
{
	if (!x && !y && !z)
	{
		ft_fprintf(2, "Error\nnull vector\n");
		return (TRUE);
	}
	return (FALSE);
}
