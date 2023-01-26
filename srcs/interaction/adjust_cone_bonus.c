/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_cone_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:56:04 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/26 11:51:48 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

static void	rotate_co(t_co *co, int key)
{
	if (key == KEY_UP)
		co->rotate.y = 1.9f;
	else if (key == KEY_DOWN)
		co->rotate.y = -1.9f;
	else if (key == NUMPAD_PLUS)
		co->rotate.z = 1.9f;
	else if (key == NUMPAD_MINUS)
		co->rotate.z = -1.9f;
	else if (key == KEY_LEFT)
		co->rotate.x = 1.9f;
	else if (key == KEY_RIGHT)
		co->rotate.x = -1.9f;
}

static void	do_transform_co(t_co *co, int key)
{
	if (key == 111)
		co->diameter -= 0.5f;
	else if (key == 112)
		co->diameter += 0.5f;
	else if (key == 65431)
		co->translate.y += 0.5f;
	else if (key == 65433)
		co->translate.y -= 0.5f;
	else if (key == 65430)
		co->translate.x -= 0.5f;
	else if (key == 65432)
		co->translate.x += 0.5f;
	else if (key == 65429)
		co->translate.z += 0.5f;
	else if (key == 65434)
		co->translate.z -= 0.5f;
	else
		rotate_co(co, key);
}

void	adjust_cone(t_stdobj *obj, int key, t_scene *scene)
{
	t_co	*co;

	co = (t_co *)obj;
	co->translate = set_vec(0, 0, 0);
	co->rotate = set_vec(0, 0, 0);
	do_transform_co(co, key);
	do_orientation(key, &co->orientation);
	set_transform(&co->translate, &co->rotate, scene);
	matrix_print(scene->fwtfm, 1);
	matrix_vec_mult(scene->fwtfm, &co->pos);
	print_vec(&co->pos);
}
