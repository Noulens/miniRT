/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:48 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/23 16:53:16 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"
#include "render.h"

int	ft_closebutton(void *param)
{
	t_scene	*scn;

	scn = (t_scene *)param;
	des_mlx(scn->ig->mlx, scn->ig->img, scn->ig->win);
	objclear(scn->objects);
	exit(0);
}

int	ft_translate_cam_test(void *param, int keycode)
{
	t_scene	*scene;
	t_vec3	cam_translate;

	scene = (t_scene *)param;
	cam_translate = set_vec(0, 0, 0);
	if (keycode == KEY_A)
		cam_translate.z += 0.1f;
	if (keycode == KEY_D)
		cam_translate.z -= 0.1f;
	// this matrix_transformation function doesn't work well except for z axis translate. Feel free to rewrite or debug.
	matrix_transformation(&(scene->cam.pos), vec_add(scene->cam.translate, cam_translate), scene->cam.rotate);
	return (0);
}

void	clear_image(t_scene *scene)
{
	ft_bzero(scene->ig->addr, scene->win_w * scene->win_h * 4);
}

int	ft_key(int keycode, void *param)
{
	t_scene	*scn;

	scn = (t_scene *)param;
	if (keycode == KEY_ESC)
		ft_closebutton(param);
	if (keycode == KEY_A || keycode == KEY_D)
		ft_translate_cam_test((void*)param, keycode);
	// printf("keycode : %i\n", keycode);
	clear_image(scn);
	render(scn);
    mlx_put_image_to_window(scn->ig->mlx, scn->ig->win, scn->ig->img, 0, 0);
	return (0);
}