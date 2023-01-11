/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:48 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/10 06:16:31 by hyunah           ###   ########.fr       */
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

int	ft_translate_cam_test(void *param, int keycode)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == KEY_D)
		scene->cam.rotate.x = -0.5f;
	if (keycode == KEY_A)
		scene->cam.rotate.x = 0.5f;
	if (keycode == KEY_W)
	{
		scene->cam.translate.z = 0.5f;
		printf("translate +: %f\n", scene->cam.translate.z);
	}
	if (keycode == KEY_S)
	{
		scene->cam.translate.z = -0.5f;
		printf("translate -: %f\n", scene->cam.translate.z);
	}
	set_transform(&scene->cam.translate, &scene->cam.rotate, scene);
	matrix_print(scene->fwtfm, 1);
	matrix_vec_mult(scene->fwtfm, &scene->cam.pos);
	printf("x: %f, z: %f\n", scene->cam.pos.x, scene->cam.pos.z);
	return (0);
}

void	clear_image(t_scene *scene)
{
	ft_bzero(scene->ig->addr, scene->win_w * scene->win_h * 4);
}

int	ft_key(int key, void *param)
{
	t_scene	*scn;

	scn = (t_scene *)param;
	if (key == KEY_ESC)
		ft_closebutton(param);
	if (key == KEY_A || key == KEY_D || key == KEY_S || key == KEY_W)
		ft_translate_cam_test((void *)param, key);
	if (key == KEY_PLUS)
		ft_rotation_x((void *)param);
	if (key == KEY_MINUS)
		ft_rotation_y((void *)param);
	if (key == KEY_UP)
		ft_rotation_z((void *)param);
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
			ft_printf("This is the background\n");
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
