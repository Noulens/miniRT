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
	t_img	*img;

	img = (t_img *)param;
	des_mlx(img->mlx, img->img, img->win);
	exit(0);
}

int	ft_translate_cam_test(void *param, int keycode)
{
	t_img	*img;
	t_vec3	cam_translate;

	img = (t_img *)param;
	cam_translate = set_vec(0, 0, 0);
	if (keycode == KEY_A)
		cam_translate.z+= 0.1;
	if (keycode == KEY_D)
		cam_translate.z-= 0.1;

	// this matrix_transformation function doesn't work well except for z axis translate. Feel free to rewrite or debug.
	matrix_transformation(&(img->scene->cam.pos), vec_add(img->scene->cam.translate, cam_translate), img->scene->cam.rotate);
	return (0);
}

void	clear_image(t_img *img)
{
	ft_bzero(img->addr, img->scene->win_w * img->scene->win_h * 4);
}

int	ft_key(int keycode, void *param)
{
	t_img	*img;

	img = (t_img *)param;
	if (keycode == KEY_ESC)
		ft_closebutton(param);
	if (keycode == KEY_A || keycode == KEY_D)
		ft_translate_cam_test((void*)param, keycode);
	// printf("keycode : %i\n", keycode);
	clear_image(img);
	render(img);
    mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}