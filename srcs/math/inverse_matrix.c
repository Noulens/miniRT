/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:57:47 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/16 16:57:49 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_func.h"

void	step4_2(t_matrix4 *t, t_matrix4 *s, t_inv *inv)
{
	while (++(*inv).p < 3)
	{
		(*inv).q = (*inv).p;
		while (++(*inv).q < 4)
		{
			(*inv).constant = (*t).m[(*inv).p][(*inv).q];
			(*inv).r = -1;
			while (++(*inv).r < 4)
			{
				(*t).m[(*inv).p][(*inv).r] -= (*t).m[(*inv).q][(*inv).r]
					* (*inv).constant;
				(*s).m[(*inv).p][(*inv).r] -= (*s).m[(*inv).q][(*inv).r]
					* (*inv).constant;
			}
			(*t).m[(*inv).p][(*inv).q] = 0.f;
		}
	}
}

t_matrix4	step4(t_matrix4 *t, t_matrix4 *s, t_inv *inv)
{
	(*inv).n = -1;
	while (++(*inv).n < 4)
	{
		(*inv).divisor = (*t).m[(*inv).n][(*inv).n];
		(*inv).o = -1;
		while (++(*inv).o < 4)
		{
			(*t).m[(*inv).n][(*inv).o] = (*t).m[(*inv).n][(*inv).o]
				/ (*inv).divisor;
			(*s).m[(*inv).n][(*inv).o] = (*s).m[(*inv).n][(*inv).o]
				/ (*inv).divisor;
		}
		(*t).m[(*inv).n][(*inv).n] = 1.f;
	}
	(*inv).p = -1;
	step4_2(t, s, inv);
	return (*s);
}

void	step3(t_matrix4 *t, t_matrix4 *s, t_inv *inv)
{
	if ((*inv).pivot != (*inv).i)
	{
		(*inv).k = -1;
		while (++(*inv).k < 4)
		{
			(*inv).tmp = (*t).m[(*inv).i][(*inv).k];
			(*t).m[(*inv).i][(*inv).k] = (*t).m[(*inv).pivot][(*inv).k];
			(*t).m[(*inv).pivot][(*inv).k] = (*inv).tmp;
			(*inv).tmp = (*s).m[(*inv).i][(*inv).k];
			(*s).m[(*inv).i][(*inv).k] = (*s).m[(*inv).pivot][(*inv).k];
			(*s).m[(*inv).pivot][(*inv).k] = (*inv).tmp;
		}
	}
	(*inv).l = (*inv).i;
	while (++(*inv).l < 4)
	{
		(*inv).f = (*t).m[(*inv).l][(*inv).i] / (*t).m[(*inv).i][(*inv).i];
		(*inv).m = -1;
		while (++(*inv).m < 4)
		{
			(*t).m[(*inv).l][(*inv).m] -= (*inv).f * (*t).m[(*inv).i][(*inv).m];
			(*s).m[(*inv).l][(*inv).m] -= (*inv).f * (*s).m[(*inv).i][(*inv).m];
		}
		(*t).m[(*inv).l][(*inv).i] = 0.f;
	}
}

t_inv	step2(t_matrix4 *t, t_inv *inv)
{
	(*inv).pivot = (*inv).i;
	(*inv).pivotsize = (*t).m[(*inv).i][(*inv).i];
	if ((*inv).pivotsize < 0)
		(*inv).pivotsize = -(*inv).pivotsize;
	(*inv).j = (*inv).i;
	while (++(*inv).j < 4)
	{
		inv->tmp = (*t).m[(*inv).j][(*inv).i];
		if (inv->tmp < 0)
			inv->tmp = -inv->tmp;
		if (inv->tmp > (*inv).pivotsize)
		{
			(*inv).pivot = (*inv).j;
			(*inv).pivotsize = inv->tmp;
		}
	}
	return (*inv);
}

/* this function returns the inverse of the matrix in parameter, only works
 * for 4*4 matrices that were initialized to the identity matrix. */

t_matrix4	inverse(t_matrix4 t)
{
	t_matrix4	s;
	t_inv		inv;

	set_identity(&s);
	inv.i = -1;
	while (++inv.i < 3)
	{
		inv = step2(&t, &inv);
		if (inv.pivotsize == 0)
			return (s);
		step3(&t, &s, &inv);
	}
	s = step4(&t, &s, &inv);
	return (s);
}
