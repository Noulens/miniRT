/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:36:57 by tnoulens          #+#    #+#             */
/*   Updated: 2023/01/11 20:37:01 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

static void	adjust_sphere(t_stdobj *obj, int key)
{
	t_sp	*sp;

	sp = (t_sp *)obj;
	if (key == 45)
		sp->diameter -= 0.5f;
	if (key == 61)
		sp->diameter += 0.5f;
	if (key == 65431)
		sp->pos.y += 0.5f;
	if (key == 65433)
		sp->pos.y -= 0.5f;
	if (key == 65430)
		sp->pos.x -= 0.5f;
	if (key == 65432)
		sp->pos.x += 0.5f;
	if (key == 65429)
		sp->pos.z += 0.5f;
	if (key == 65434)
		sp->pos.z -= 0.5f;
}

static void	adjust_cylinder(t_stdobj *obj, int key)
{
	t_cy	*cy;

	cy = (t_cy *)obj;
	if (key == 45)
		cy->diameter -= 0.5f;
	if (key == 61)
		cy->diameter += 0.5f;
}

static void	key_plan(int key, t_pl*pl)
{
	if (key == 48)
		pl->orientation.y -= 0.1f;
	if (key == 57)
		pl->orientation.y += 0.1f;
	if (key == 56)
		pl->orientation.x -= 0.1f;
	if (key == 55)
		pl->orientation.x += 0.1f;
	if (key == 45)
		pl->orientation.z -= 0.1f;
	if (key == 61)
		pl->orientation.z += 0.1f;
	if (key == 65431)
		pl->pos.y += 0.5f;
	if (key == 65433)
		pl->pos.y -= 0.5f;
	if (key == 65430)
		pl->pos.x -= 0.5f;
	if (key == 65432)
		pl->pos.x += 0.5f;
	if (key == 65429)
		pl->pos.z += 0.5f;
	if (key == 65434)
		pl->pos.z -= 0.5f;
}

static void	adjust_plan(t_stdobj *obj, int key)
{
	t_pl	*pl;

	pl = (t_pl *)obj;
	key_plan(key, pl);
}

int	modify_objects(void *param, int key)
{
	t_scene	*scn;

	scn = (t_scene *)param;
	if (scn->target == -1)
		return (ft_printf("No object selected\n"), 0);
	if (scn->objtab[scn->target - 1]->objtp == SP)
		adjust_sphere(scn->objtab[scn->target - 1]->obj, key);
	else if (scn->objtab[scn->target - 1]->objtp == CY)
		adjust_cylinder(scn->objtab[scn->target - 1]->obj, key);
	else if (scn->objtab[scn->target - 1]->objtp == PL)
		adjust_plan(scn->objtab[scn->target - 1]->obj, key);
	return (0);
}
