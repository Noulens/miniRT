/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:48 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/01 18:16:37 by hyujung          ###   ########.fr       */
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
		scene->cam.translate.x += 0.5f;
	else if (keycode == KEY_A)
		scene->cam.translate.x -= 0.5f;
	else if (keycode == KEY_W)
		scene->cam.translate.z += 0.5f;
	else if (keycode == KEY_S)
		scene->cam.translate.z -= 0.5f;
	else if (keycode == KEY_SPACE)
		scene->cam.translate.y += 0.5f;
	else if (keycode == KEY_CTRL)
		scene->cam.translate.y -= 0.5f;
	else if (keycode == KEY_UP)
		scene->cam.rotate.y += 3.f;
	else if (keycode == KEY_DOWN)
		scene->cam.rotate.y -= 3.f;
	else if (keycode == NUMPAD_PLUS)
		scene->cam.rotate.z += 3.f;
	else if (keycode == NUMPAD_MINUS)
		scene->cam.rotate.z -= 3.f;
	else if (keycode == KEY_LEFT)
		scene->cam.rotate.x += 3.f;
	else if (keycode == KEY_RIGHT)
		scene->cam.rotate.x -= 3.f;
}

int	move_cam(void *param, int keycode)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	do_transform(keycode, scene);
	return (0);
}

int	ft_key(int key, void *param)
{
	t_scene	*scn;

	scn = (t_scene *)param;
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
	else if (is_objkey(key) && scn->target != -3)
		modify_objects((void *)param, key);
	else if (key == KEY_T)
		copy_paste(scn);
	else if (key == KEY_Y)
		save_scene(scn);
	clear_image(scn);
	render(scn, scn->func_ptr);
	mlx_put_image_to_window(scn->ig->mlx, scn->ig->win, scn->ig->img, 0, 0);
	if (put_debug_to_window(scn->ig->mlx, scn->ig->win, scn))
		return (ft_closebutton(param), 1);
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
		{
			ft_printf("This is the background\nx=%d\ny=%d\n, x, y");
			sn->target = -3;
		}
		mlx_put_image_to_window(sn->ig->mlx, sn->ig->win, \
		sn->ig->img, 0, 0);
		if (put_debug_to_window(sn->ig->mlx, sn->ig->win, sn))
			return (ft_closebutton(param), 1);
	}
	return (0);
}
