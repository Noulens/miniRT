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
	t_vec3	cam_translate;

	scene = (t_scene *)param;
	cam_translate = set_vec(0, 0, 0);
	if (keycode == KEY_D)
		cam_translate.x += 0.1f;
	if (keycode == KEY_A)
		cam_translate.x -= 0.1f;
	if (keycode == KEY_W)
		cam_translate.z += 0.1f;
	if (keycode == KEY_S)
		cam_translate.z -= 0.1f;
	// this matrix_transformation function doesn't work well except for z axis translate. Feel free to rewrite or debug.
	matrix_transformation(&(scene->cam.pos), vec_add(scene->cam.translate, cam_translate), scene->cam.rotate);
	return (0);
}

void	clear_image(t_scene *scene)
{
	ft_bzero(scene->ig->addr, scene->win_w * scene->win_h * 4);
}

//printf("key : %i\n", key);
int	ft_key(int key, void *param)
{
	t_scene	*scn;

	scn = (t_scene *)param;
	if (key == KEY_ESC)
		ft_closebutton(param);
	if (key == KEY_A || key == KEY_D || key == KEY_S || key == KEY_W)
		ft_translate_cam_test((void*)param, key);
	clear_image(scn);
	render(scn, scn->func_ptr);
    mlx_put_image_to_window(scn->ig->mlx, scn->ig->win, scn->ig->img, 0, 0);
	return (0);
}

int	on_click(int code, int x, int y, void *param)
{
	t_scene	*sn;
	t_ray	ray;
	int 	k;

	k = 0;
	sn = (t_scene *)param;
	ray = build_camera_ray(sn, x, y);
	if (code == 1)
	{
		while (k < 2)
		{
			if ((*sn->func_ptr[sn->objtab[k]->objtp])(ray, sn->objtab[k], k))
			{
				sn->target = sn->objtab[k]->objid;
				ft_printf(RESET"click on object nb %d:\nx = %d\ny = %d\n",
						sn->target, x, y);
				return (1);
			}
			k++;
		}
	}
	return (0);
}
