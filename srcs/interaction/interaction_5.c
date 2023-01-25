/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:13:43 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/25 18:40:25 by hyunah           ###   ########.fr       */
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
	// print_vec(&light->pos);
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
			return (0);
		return (0);
	}
	if (scene->target_light != -1)
		do_transform_light(keycode, scene);
	else
		ft_printf("target is -1\n");
	return (1);
}

char	*ft_ftoa(float a, int precision)
{
	int		i;
	char	*integer;
	char	*flo;
	char	*tmp;
	char	*ret;

	ret = NULL;
	i = -1;
	integer = ft_itoa((int)a);
	flo = malloc(sizeof(char) * precision + 1);
	if (!flo)
		return (NULL);
	a = a - (int)a;
	while (++i < precision)
	{
		a *= 10;
		if (a == 0)
			flo[i] = 0 + '0';
		else
		{
			tmp = ft_itoa(a);
			flo[i] = tmp[0];
			free(tmp);
			a = a - (int)a;
		}
	}
	flo[precision] = '\0';
	ret = ft_strjoinsep(integer, flo, ".");
	free(integer);
	free(flo);
	return (ret);
}

char	*vec_to_string(t_vec3 vec)
{
	char	*x;
	char	*y;
	char	*z;
	char	*ret;

	x = ft_ftoa(vec.x, 3);
	y = ft_ftoa(vec.y, 3);
	z = ft_ftoa(vec.z, 3);
	ret = ft_strjoinsep(x, y, " ");
	ret = ft_strjoinsep(ret, z, " ");
	free(x);
	free(y);
	free(z);
	return (ret);
}

void	put_debug_to_window(void *mlx, void *win, t_scene *s)
{
	char	*t;
	char	*r;

	mlx_string_put(mlx, win, 10, 10, ft_trgb(255, 255, 255, 255), "MiniRT");
	mlx_string_put(mlx, win, 10, 25, ft_trgb(255, 255, 255, 255), "camera : [C], light : [L], object : click object");
	if (s->target == -1)
	{
		mlx_string_put(mlx, win, 10, 50, ft_trgb(255, 255, 255, 255), "Mode : Camera");
		mlx_string_put(mlx, win, 10, 60, ft_trgb(255, 255, 255, 255), "Translate");
		mlx_string_put(mlx, win, 10, 75, ft_trgb(255, 255, 255, 255), "[ a ] - X + [ d ]");
		mlx_string_put(mlx, win, 10, 90, ft_trgb(255, 255, 255, 255), "[ctr] - Y + [space]");
		mlx_string_put(mlx, win, 10, 105, ft_trgb(255, 255, 255, 255), "[ s ] - Z + [ w ]");
		t = vec_to_string(s->cam.translate);
		mlx_string_put(mlx, win, 10, 120, ft_trgb(255, 255, 255, 255), t);
		free(t);
		mlx_string_put(mlx, win, 10, 60+90, ft_trgb(255, 255, 255, 255), "Rotate");
		mlx_string_put(mlx, win, 10, 75+90, ft_trgb(255, 255, 255, 255), "[right] - X + [left]");
		mlx_string_put(mlx, win, 10, 90+90, ft_trgb(255, 255, 255, 255), "[down] - Y + [up]");
		mlx_string_put(mlx, win, 10, 105+90, ft_trgb(255, 255, 255, 255), "[-] - Z + [+]");
		r = vec_to_string(s->cam.rotate);
		mlx_string_put(mlx, win, 10, 120+90, ft_trgb(255, 255, 255, 255), r);
		free(r);
	}
	else if (s->target == -2)
	{
		mlx_string_put(mlx, win, 10, 50, ft_trgb(255, 255, 255, 255), "Mode : Light");
		if (s->target_light == -1)
			mlx_string_put(mlx, win, 10, 60, ft_trgb(255, 255, 255, 255), "Select light by num keypad. / Not available");
		else
		{
			mlx_string_put(mlx, win, 100, 50, ft_trgb(255, 255, 255, 255), s->msg);
			mlx_string_put(mlx, win, 10, 60, ft_trgb(255, 255, 255, 255), "Translate");
			mlx_string_put(mlx, win, 10, 75, ft_trgb(255, 255, 255, 255), "[ A ] - X + [ D ]");
			mlx_string_put(mlx, win, 10, 90, ft_trgb(255, 255, 255, 255), "[CTR] - Y + [SPACE]");
			mlx_string_put(mlx, win, 10, 105, ft_trgb(255, 255, 255, 255), "[ S ] - Z + [ W ]");
			t = vec_to_string(s->lamptab[s->target_light]->pos);
			mlx_string_put(mlx, win, 10, 120, ft_trgb(255, 255, 255, 255), t);
			free(t);
			mlx_string_put(mlx, win, 10, 60+90, ft_trgb(255, 255, 255, 255), "[down] - Brightness + [up]");
			r = ft_ftoa(s->lamptab[s->target_light]->brightness, 1);
			mlx_string_put(mlx, win, 10, 120+90, ft_trgb(255, 255, 255, 255), "brightness: ");
			mlx_string_put(mlx, win, 100, 120+90, ft_trgb(255, 255, 255, 255), r);
			free(r);
		}
	}
	else if (s->target == 0)
	{
		mlx_string_put(mlx, win, 10, 50, ft_trgb(255, 255, 255, 255), "Mode : B G");
	}
	else
	{
		mlx_string_put(mlx, win, 10, 50, ft_trgb(255, 255, 255, 255), "Mode : Object");
		if (s->objtab[s->target -1]->objtp == 0)
		{
			mlx_string_put(mlx, win, 10, 60+90, ft_trgb(255, 255, 255, 255), "[ O ] - Diameter + [ P ]");
			t_sp	*sp;
			sp = s->objtab[s->target - 1]->obj;
			t = vec_to_string(sp->pos);
			mlx_string_put(mlx, win, 10, 120, ft_trgb(255, 255, 255, 255), t);
			free(t);
			r = ft_ftoa(sp->diameter, 1);
			mlx_string_put(mlx, win, 10, 120+90, ft_trgb(255, 255, 255, 255), "Diameter: ");
			mlx_string_put(mlx, win, 100, 120+90, ft_trgb(255, 255, 255, 255), r);
			free(r);
			printf("This is shpere\n");
			t = "Sphere";
		}
		if (s->objtab[s->target -1]->objtp == 2)
		{
			printf("This is plan\n");
			t = "Plan";
		}
		if (s->objtab[s->target -1]->objtp == 1)
		{
			printf("This is cylindre\n");
			t = "Cylindre";
		}
		if (s->objtab[s->target -1]->objtp == 3)
		{
			printf("This is cone\n");
			t = "Cone";
		}
		mlx_string_put(mlx, win, 100, 50, ft_trgb(255, 255, 255, 255), t);
		mlx_string_put(mlx, win, 10, 60, ft_trgb(255, 255, 255, 255), "Translate");
		mlx_string_put(mlx, win, 10, 75, ft_trgb(255, 255, 255, 255), "[ 4 ] - X + [ 6 ]");
		mlx_string_put(mlx, win, 10, 90, ft_trgb(255, 255, 255, 255), "[ 7 ] - Y + [ 9 ]");
		mlx_string_put(mlx, win, 10, 105, ft_trgb(255, 255, 255, 255), "[ 8 ] - Z + [ 2 ]");
	}
}