/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:28:05 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/06 18:28:09 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	do_orientation(int key, t_vec3 *orientation)
{
	if (key == 48)
		printf("orientation: %f\n", orientation->y -= 0.1f);
	else if (key == 57)
		printf("orientation: %f\n", orientation->y += 0.1f);
	else if (key == 56)
		printf("orientation: %f\n", orientation->x -= 0.1f);
	else if (key == 55)
		printf("orientation: %f\n", orientation->x += 0.1f);
	else if (key == 45)
		printf("orientation: %f\n", orientation->z -= 0.1f);
	else if (key == 61)
		printf("orientation: %f\n", orientation->z += 0.1f);
}

int	is_keycam(int key)
{
	return (key == KEY_A || key == KEY_D || key == KEY_S
		|| key == KEY_W || key == KEY_SPACE || key == KEY_CTRL
		|| key == KEY_PLUS || key == KEY_MINUS || key == KEY_UP
		|| key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT
		|| key == 61 || key == 48 || key == 57 || key == 56 || key == 55
		|| key == 45 || key == 111 || key == 112);
}

int	is_objkey(int key)
{
	return (key == KEY_A || key == KEY_D || key == KEY_S
		|| key == KEY_W || key == KEY_SPACE || key == KEY_CTRL
		|| key == KEY_PLUS || key == KEY_MINUS || key == KEY_UP
		|| key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT
		|| key == 57 || key == 55 || key == 45 || key == 61 || key == 65429
		|| key == 65430 || key == 65431 || key == 65432 || key == 65433
		|| key == 65434 || key == 48 || key == 56 || key == 111 || key == 112
		|| key == 107 || key == 108);
}

//printf("%f, %f\n", scn->cam.pos.y, scn->cam.pos.z);
//ft_printf("+ pressed\n");
/*
void	ft_rotation_x(void *obj)
{
	float	dy;
	float	dz;
	t_scene	*scn;
	t_sp	*sp;
	int 	k;

	scn = (t_scene *)obj;
	dy = scn->cam.pos.y;
	dz = scn->cam.pos.z;
	scn->cam.pos.y = dy * cosf(+0.09f) + dz * sinf(+0.09f);
	scn->cam.pos.z = -dy * sinf(+0.09f) + dz * cosf(+0.09f);
	dy = scn->cam.orientation.y;
	dz = scn->cam.orientation.z;
	scn->cam.orientation.y = dy * cosf(+0.09f) + dz * sinf(+0.09f);
	scn->cam.orientation.z = -dy * sinf(+0.09f) + dz * cosf(+0.09f);
	k = -1;
	while (++k < 3)
	{
		sp = (t_sp *)scn->objtab[k]->obj;
		dy = sp->pos.y;
		dz = sp->pos.z;
		sp->pos.y = dy * cosf(+0.09f) + dz * sinf(+0.09f);
		sp->pos.z = -dy * sinf(+0.09f) + dz * cosf(+0.09f);
	}
	printf("%d\n", scn->target);
}

void	ft_rotation_y(void *obj)
{
	float	dx;
	float	dz;
	t_scene	*scn;
	t_sp	*sp;
	int 	k;

	scn = (t_scene *)obj;
	dx = scn->cam.pos.x;
	dz = scn->cam.pos.z;
	scn->cam.pos.x = dx * cosf(+0.09f) + dz * sinf(+0.09f);
	scn->cam.pos.z = -dx * sinf(+0.09f) + dz * cosf(+0.09f);
	dx = scn->cam.orientation.x;
	dz = scn->cam.orientation.z;
	scn->cam.orientation.x = dx * cosf(+0.09f) + dz * sinf(+0.09f);
	scn->cam.orientation.z = -dx * sinf(+0.09f) + dz * cosf(+0.09f);
	k = -1;
	while (++k < 3)
	{
		sp = (t_sp *)scn->objtab[k]->obj;
		dx = sp->pos.x;
		dz = sp->pos.z;
		sp->pos.x = dx * cosf(+0.09f) + dz * sinf(+0.09f);
		sp->pos.z = -dx * sinf(+0.09f) + dz * cosf(+0.09f);
	}
}

void	ft_rotation_z(void *obj)
{
	float	dx;
	float	dy;
	t_scene	*scn;
	t_sp	*sp;
	int 	k;

	scn = (t_scene *)obj;
	dx = scn->cam.pos.x;
	dy = scn->cam.pos.y;
	scn->cam.pos.x = dx * cosf(+0.09f) - dy * sinf(+0.09f);
	scn->cam.pos.y= dx * sinf(+0.09f) + dy * cosf(+0.09f);
	dy = scn->cam.orientation.y;
	dx = scn->cam.orientation.x;
	scn->cam.orientation.x = dx * cosf(+0.09f) - dy * sinf(+0.09f);
	scn->cam.orientation.y= dx * sinf(+0.09f) + dy * cosf(+0.09f);
	k = -1;
	while (++k < 3)
	{
		sp = (t_sp *)scn->objtab[k]->obj;
		dx = sp->pos.x;
		dy = sp->pos.y;
		sp->pos.x = dx * cosf(+0.09f) - dy * sinf(+0.09f);
		sp->pos.y = dx * sinf(+0.09f) + dy * cosf(+0.09f);
	}
}
*/
