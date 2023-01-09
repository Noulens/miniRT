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

	scn = (t_scene *)obj;
	dy = scn->cam.pos.y;
	dz = scn->cam.pos.z;
	scn->cam.pos.y = dy * cosf(+0.09f) + dz * sinf(+0.09f);
	scn->cam.pos.z = -dy * sinf(+0.09f) + dz * cosf(+0.09f);
	sp = (t_sp *)scn->objtab[0];
	dy = sp->pos.y;
	dz = sp->pos.z;
}

void	ft_rotation_y(void *obj)
{
	float	dx;
	float	dz;
	t_scene	*scn;

	scn = (t_scene *)obj;
	dx = scn->cam.pos.x;
	dz = scn->cam.pos.z;
	scn->cam.pos.x = dx * cosf(+0.09f) + dz * sinf(+0.09f);
	scn->cam.pos.z = -dx * sinf(+0.09f) + dz * cosf(+0.09f);
}

void	ft_rotation_z(void *obj)
{
	float	dx;
	float	dy;
	t_scene	*scn;

	scn = (t_scene *)obj;
	dx = scn->cam.pos.x;
	dy = scn->cam.pos.y;
	scn->cam.pos.x = dx * cosf(+0.09f) - dy * sinf(+0.09f);
	scn->cam.pos.y= dx * sinf(+0.09f) + dy * cosf(+0.09f);
}
