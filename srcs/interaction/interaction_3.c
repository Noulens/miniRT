/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:46:57 by tnoulens          #+#    #+#             */
/*   Updated: 2023/02/02 16:55:49 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	do_transform_s(t_sp *sp, int key)
{
	if (key == 111)
		sp->diameter -= 0.5f;
	else if (key == 112)
		sp->diameter += 0.5f;
	else if (key == 65431)
		sp->translate.y += 0.5f;
	else if (key == 65433)
		sp->translate.y -= 0.5f;
	else if (key == 65430)
		sp->translate.x -= 0.5f;
	else if (key == 65432)
		sp->translate.x += 0.5f;
	else if (key == 65429)
		sp->translate.z += 0.5f;
	else if (key == 65434)
		sp->translate.z -= 0.5f;
	if (sp->diameter <= 0)
		sp->diameter = 0.5f;
}

void	rotate_cylinder(t_cy *cy, int key)
{
	if (key == KEY_0)
		cy->rotate.y = 1.9f;
	else if (key == KEY_9)
		cy->rotate.y = -1.9f;
	else if (key == KEY_PLUS)
		cy->rotate.z = 1.9f;
	else if (key == KEY_MINUS)
		cy->rotate.z = -1.9f;
	else if (key == KEY_8)
		cy->rotate.x = 1.9f;
	else if (key == KEY_7)
		cy->rotate.x = -1.9f;
}

void	rotate_plan(t_pl *pl, int key)
{
	if (key == KEY_UP)
		pl->rotate.y += 10.f;
	else if (key == KEY_DOWN)
		pl->rotate.y += -10.f;
	else if (key == NUMPAD_PLUS)
		pl->rotate.z += 10.f;
	else if (key == NUMPAD_MINUS)
		pl->rotate.z += -10.f;
	else if (key == KEY_LEFT)
		pl->rotate.x += 10.f;
	else if (key == KEY_RIGHT)
		pl->rotate.x += -10.f;
}

void	do_transform_c(t_cy *cy, int key)
{
	if (key == 111 && (cy->diameter - 0.5f > 0))
		cy->diameter -= 0.5f;
	else if (key == 112)
		cy->diameter += 0.5f;
	else if (key == 117 && (cy->height - 0.5f >= 0))
		cy->height -= 0.5f;
	else if (key == 105)
		cy->height += 0.5f;
	else if (key == NUMPAD_8)
		cy->translate.y += 0.5f;
	else if (key == NUMPAD_2)
		cy->translate.y -= 0.5f;
	else if (key == NUMPAD_4)
		cy->translate.x -= 0.5f;
	else if (key == NUMPAD_6)
		cy->translate.x += 0.5f;
	else if (key == NUMPAD_7)
		cy->translate.z += 0.5f;
	else if (key == NUMPAD_9)
		cy->translate.z -= 0.5f;
	else
		rotate_cylinder(cy, key);
}

void	do_transform_p(t_pl *pl, int key)
{
	if (key == 65431)
		pl->translate.y += 0.5f;
	else if (key == 65433)
		pl->translate.y -= 0.5f;
	else if (key == 65430)
		pl->translate.x -= 0.5f;
	else if (key == 65432)
		pl->translate.x += 0.5f;
	else if (key == 65429)
		pl->translate.z += 0.5f;
	else if (key == 65434)
		pl->translate.z -= 0.5f;
	else
		rotate_plan(pl, key);
	pl->u_axis = set_vec(INFINITY, INFINITY, INFINITY);
	pl->v_axis = set_vec(INFINITY, INFINITY, INFINITY);
	pl->hit_normal = set_vec(INFINITY, INFINITY, INFINITY);
}
