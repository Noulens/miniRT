/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:48 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/25 14:05:37 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

int	ft_closebutton(void *param)
{
	t_scene	*scn;

	scn = (t_scene *)param;
	des_mlx(scn->ig->mlx, scn->ig->img, scn->ig->win);
	des_minirt(scn);
	exit(EXIT_SUCCESS);
}

void	do_transform(int keycode, t_scene *scene)
{
	if (keycode == KEY_D)
		scene->cam.translate.x += 0.1f;
	else if (keycode == KEY_A)
		scene->cam.translate.x -= 0.1f;
	else if (keycode == KEY_W)
		scene->cam.translate.z += 0.1f;
	else if (keycode == KEY_S)
		scene->cam.translate.z -= 0.1f;
	else if (keycode == KEY_SPACE)
		scene->cam.translate.y += 0.1f;
	else if (keycode == KEY_CTRL)
		scene->cam.translate.y -= 0.1f;
	else if (keycode == KEY_UP)
		scene->cam.rotate.y += 1.9f;
	else if (keycode == KEY_DOWN)
		scene->cam.rotate.y -= 1.9f;
	else if (keycode == KEY_PLUS)
		scene->cam.rotate.z += 1.9f;
	else if (keycode == KEY_MINUS)
		scene->cam.rotate.z -= 1.9f;
	else if (keycode == KEY_LEFT)
		scene->cam.rotate.x += 1.9f;
	else if (keycode == KEY_RIGHT)
		scene->cam.rotate.x -= 1.9f;
}

int	move_cam(void *param, int keycode)
{
	t_scene	*scene;
	t_vec3	vec_null;

	vec_null = set_vec(0, 0, 0);
	scene = (t_scene *)param;
	do_transform(keycode, scene);
	do_orientation(keycode, &scene->cam.orientation);
	set_transform(&scene->cam.translate, &vec_null, scene);
	matrix_print(scene->fwtfm, 1);
	matrix_vec_mult(scene->fwtfm, &scene->cam.pos);
	print_vec(&scene->cam.pos);
	return (0);
}

int	find_light(t_scene *s, int keycode)
{
	int	num[9] = {NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5, NUMPAD_6, NUMPAD_7, NUMPAD_8, NUMPAD_9};
	int	i;

	i = -1;
	while (++i < s->num_lamps)
	{
		if (num[i] == keycode)
			return (ft_printf("numpad %i clicked\n", i + 1), i);
	}
	return (-1);
}

void	do_transform_light(int keycode, t_scene *scene)
{
	if (keycode == KEY_D)
		scene->lamptab[scene->target_light]->pos.x += 0.1f;
	else if (keycode == KEY_A)
		scene->lamptab[scene->target_light]->pos.x -= 0.1f;
	else if (keycode == KEY_W)
		scene->lamptab[scene->target_light]->pos.z += 0.1f;
	else if (keycode == KEY_S)
		scene->lamptab[scene->target_light]->pos.z -= 0.1f;
	else if (keycode == KEY_SPACE)
		scene->lamptab[scene->target_light]->pos.y += 0.1f;
	else if (keycode == KEY_CTRL)
		scene->lamptab[scene->target_light]->pos.y -= 0.1f;
	else if (keycode == KEY_UP)
		scene->lamptab[scene->target_light]->brightness += 0.1f;
	else if (keycode == KEY_DOWN)
		scene->lamptab[scene->target_light]->brightness -= 0.1;
	if (scene->lamptab[scene->target_light]->brightness >= 1)
		scene->lamptab[scene->target_light]->brightness = 1;
	if (scene->lamptab[scene->target_light]->brightness <= 0)
		scene->lamptab[scene->target_light]->brightness = 0;

}

int	move_light(void *param, int keycode)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (is_lightkey(keycode))
	{
		scene->target_light = find_light(scene, keycode);
		if (scene->target_light == -1)
			return (ft_printf("No light available\n"), 0);
		return (0);
	}
	if (scene->target_light != -1)
	{
		do_transform_light(keycode, scene);
		print_vec(&scene->lamptab[scene->target_light]->pos);
	}
	else
		ft_printf("target is -1\n");
	return (1);
}

// TODO: remove this printf
int	ft_key(int key, void *param)
{
	t_scene	*scn;

	scn = (t_scene *)param;
	ft_printf("%d\n", key);
	if (key == KEY_ESC)
		ft_closebutton(param);
	else if (key == KEY_C)
		scn->target = -1;
	else if (scn->target == -1 && is_keycam(key))
		move_cam((void *)param, key);
	else if (key == KEY_L)
		scn->target = -2;
	else if (scn->target == -2 && (is_keycam(key) || is_lightkey(key)))
		move_light((void *)param, key);
	else if (is_objkey(key))
		modify_objects((void *)param, key);
	clear_image(scn);
	render(scn, scn->func_ptr);
	mlx_put_image_to_window(scn->ig->mlx, scn->ig->win, scn->ig->img, 0, 0);
	return (0);
}

int	on_click(int code, int x, int y, void *param)
{
	t_scene	*sn;
	int		k;

	sn = (t_scene *)param;
	if (code == 1)
	{
		k = compute_pixel(sn, x, y, sn->func_ptr);
		if (k != -1)
		{
			sn->target = k + 1;
			ft_printf("This is object nb %d\nx=%d\ny=%d\n", sn->target, x, y);
		}
		else
			ft_printf("This is the background\nx=%d\ny=%d\n, x, y");
	}
	return (0);
}

// this code can be used in on_click:

// t_ray	ray;
//
// ray = build_camera_ray(sn, x, y);
// if (code == 1)
// {
// 	while (k < 2)
// 	{
// 		if ((*sn->func_ptr[sn->objtab[k]->objtp])(ray,
// 				sn->objtab[k], &hit_dist))
// 		{
// 			sn->target = sn->objtab[k]->objid;
// 			ft_printf(RESET"click on object nb %d:\nx = %d\ny = %d\n",
// 					sn->target, x, y);
// 			return (1);
// 		}
// 		k++;
// 	}
// }
