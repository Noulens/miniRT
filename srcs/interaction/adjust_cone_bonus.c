/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_cone_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:56:04 by tnoulens          #+#    #+#             */
/*   Updated: 2023/02/02 17:00:14 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

static void	rotate_co(t_co *cy, int key)
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

static void	do_transform_co(t_co *cy, int key)
{
	if (key == 111 && (cy->rad - 0.5f > 0))
		cy->rad -= 0.5f;
	else if (key == 112)
		cy->rad += 0.5f;
	else if (key == 117 && (cy->height - 0.5f > 0))
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
		rotate_co(cy, key);
}

void	adjust_cone(t_stdobj *obj, int key, t_scene *scene)
{
	t_co	*cy;

	cy = (t_co *)obj;
	cy->translate = set_vec(0, 0, 0);
	cy->rotate = set_vec(0, 0, 0);
	do_transform_co(cy, key);
	do_orientation(key, &cy->orientation);
	set_transform(&cy->translate, &cy->rotate, scene);
	matrix_vec_mult(scene->fwtfm, &cy->pos);
	ft_fprintf(2, "Cone adjustment ok\n");
}
