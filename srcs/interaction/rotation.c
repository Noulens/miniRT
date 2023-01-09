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

//printf("%f, %f\n", scn->cam.pos.y, scn->cam.pos.z);
//ft_printf("+ pressed\n");

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
	while (++k < 2)
	{
		sp = (t_sp *)scn->objtab[k]->obj;
		dy = sp->pos.y;
		dz = sp->pos.z;
		sp->pos.y = dy * cosf(+0.09f) + dz * sinf(+0.09f);
		sp->pos.z = -dy * sinf(+0.09f) + dz * cosf(+0.09f);
	}
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
	while (++k < 2)
	{
		sp = (t_sp *) scn->objtab[k]->obj;
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
	while (++k < 2)
	{
		sp = (t_sp *) scn->objtab[k]->obj;
		dx = sp->pos.x;
		dy = sp->pos.y;
		sp->pos.x = dx * cosf(+0.09f) - dy * sinf(+0.09f);
		sp->pos.y = dx * sinf(+0.09f) + dy * cosf(+0.09f);
	}
}
