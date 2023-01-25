/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:13:43 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/25 15:12:34 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	do_transform_light(int keycode, t_scene *scene)
{
	t_light	*light;

	light = scene->lamptab[scene->target_light];
	if (keycode == KEY_D)
		light->pos.x += 0.1f;
	else if (keycode == KEY_A)
		light->pos.x -= 0.1f;
	else if (keycode == KEY_W)
		light->pos.z += 0.1f;
	else if (keycode == KEY_S)
		light->pos.z -= 0.1f;
	else if (keycode == KEY_SPACE)
		light->pos.y += 0.1f;
	else if (keycode == KEY_CTRL)
		light->pos.y -= 0.1f;
	else if (keycode == KEY_UP)
		light->brightness += 0.1f;
	else if (keycode == KEY_DOWN)
		light->brightness -= 0.1;
	if (light->brightness >= 1)
		light->brightness = 1;
	if (light->brightness <= 0)
		light->brightness = 0;
}

int	find_light(t_scene *s, int keycode)
{
	int	num[9] = {NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5, \
					NUMPAD_6, NUMPAD_7, NUMPAD_8, NUMPAD_9};
	int	i;

	i = -1;
	while (++i < s->num_lamps)
	{
		if (num[i] == keycode)
		{
			s->msg = ft_itoa(i + 1);
			return (i);
		}
	}
	return (-1);
}

int	move_light(void *param, int keycode)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (is_lightkey(keycode))
	{
		scene->target_light = find_light(scene, keycode);
		if (scene->target_light == -1)
		{
			scene->msg = "No light available";
			return (0);
		}
		return (0);
	}
	if (scene->target_light != -1)
		do_transform_light(keycode, scene);
	else
		ft_printf("target is -1\n");
	return (1);
}

void	put_debug_to_window(void *mlx, void *win, t_scene *s)
{
	mlx_string_put(mlx, win, 10, 10, ft_trgb(255, 255, 255, 255), "MiniRT");
	mlx_string_put(mlx, win, 10, 25, ft_trgb(255, 255, 255, 255), "camera : [c], light : [l], object : click object");
	if (s->target == -1)
	{
		mlx_string_put(mlx, win, 10, 50, ft_trgb(255, 255, 255, 255), "Mode : Camera");
	}
	else if (s->target == -2)
	{
		mlx_string_put(mlx, win, 10, 50, ft_trgb(255, 255, 255, 255), "Mode : Light");
		if (s->target_light == -1)
			mlx_string_put(mlx, win, 50, 25, ft_trgb(255, 255, 255, 255), "Select light by num keypad.");
		else
			mlx_string_put(mlx, win, 75, 25, ft_trgb(255, 255, 255, 255), s->msg);

	}
	else
		mlx_string_put(mlx, win, 10, 50, ft_trgb(255, 255, 255, 255), "Mode : Object");
}