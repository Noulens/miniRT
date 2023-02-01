/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:36:57 by tnoulens          #+#    #+#             */
/*   Updated: 2023/02/01 18:09:15 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	adjust_sphere(void *param, int keycode, t_scene *scene)
{
	t_sp	*sp;

	sp = (t_sp *)param;
	sp->translate = set_vec(0, 0, 0);
	sp->rotate = set_vec(0, 0, 0);
	do_transform_s(sp, keycode);
	set_transform(&sp->translate, &sp->rotate, scene);
	matrix_vec_mult(scene->fwtfm, &sp->pos);
	ft_fprintf(2, "Sphere adjustment ok\n");
}

static void	adjust_cylinder(t_stdobj *obj, int key, t_scene *scene)
{
	t_cy	*cy;

	cy = (t_cy *)obj;
	cy->translate = set_vec(0, 0, 0);
	cy->rotate = set_vec(0, 0, 0);
	do_transform_c(cy, key);
	do_orientation(key, &cy->orientation);
	set_transform(&cy->translate, &cy->rotate, scene);
	matrix_vec_mult(scene->fwtfm, &cy->pos);
	ft_fprintf(2, "Cylinder adjustment ok\n");
}

static void	adjust_plan(t_stdobj *obj, int key, t_scene *scene)
{
	t_pl	*pl;

	pl = (t_pl *)obj;
	(void)scene;
	do_transform_p(pl, key);
	ft_fprintf(2, "Plan adjustment ok\n");
}

int	modify_objects(void *param, int key)
{
	t_scene	*scn;

	scn = (t_scene *)param;
	if (scn->target == -1)
		return (ft_printf("No object selected, camera is active\n"), 0);
	if (scn->target == -2)
		return (ft_printf("No object selected, light is active\n"), 0);
	if (scn->objtab[scn->target - 1]->objtp == SP)
		adjust_sphere(scn->objtab[scn->target - 1]->obj, key, scn);
	else if (scn->objtab[scn->target - 1]->objtp == CY)
		adjust_cylinder(scn->objtab[scn->target - 1]->obj, key, scn);
	else if (scn->objtab[scn->target - 1]->objtp == PL)
		adjust_plan(scn->objtab[scn->target - 1]->obj, key, scn);
	else if (BONUS == 1 && scn->objtab[scn->target - 1]->objtp == CO)
		adjust_cone(scn->objtab[scn->target - 1]->obj, key, scn);
	return (0);
}

int	move_light(void *param, int keycode)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (is_lightkey(keycode))
	{
		scene->target_light = find_light(scene, keycode);
		if (scene->target_light == -1)
			return (0);
		return (0);
	}
	if (scene->target_light == 0)
	{
		if (keycode == KEY_UP)
			scene->alight.al += 0.1f;
		if (keycode == KEY_DOWN)
			scene->alight.al -= 0.1f;
		keep_between_zero_one(&scene->alight.al);
	}
	else if (scene->target_light != -1)
		do_transform_light(keycode, scene);
	else
		ft_printf("target is -1\n");
	return (1);
}
