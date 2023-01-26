/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_interaction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:10:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/26 07:47:54 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

int	print_xyz(t_scene *s, char *param, char *inst[4], int a)
{
	int		gap;
	int		i;
	char	*str;
	char	*ret;

	gap = 15;
	str = "----";
	param = ft_strjoinsep(str, param, " ");
	ret = ft_strjoinsep(param, str, " ");
	mlx_string_put(s->ig->mlx, s->ig->win, 10, a, -1, ret);
	free(ret);
	i = -1;
	while (inst[++i])
		mlx_string_put(s->ig->mlx, s->ig->win, \
		10, a + (gap * (i + 1)), -1, inst[i]);
	return (a + (gap * i));
}

int	print_v(t_scene *s, t_vec3 v, int i, int gap)
{
	char	*str;

	str = vec_to_string(v);
	mlx_string_put(s->ig->mlx, s->ig->win, 30, i + gap, -1, str);
	free(str);
	return (i + gap);
}

int	print_f(t_scene *s, float f, int i, int gap)
{
	char	*str;

	str = ft_ftoa(f, 1);
	mlx_string_put(s->ig->mlx, s->ig->win, 30, i + gap, -1, str);
	free(str);
	return (i + gap);
}

void	put_debug_to_window_obj(t_scene *s, char *rot[4])
{
	t_vec3	pos;
	int		i;
	char	*tmp[4];

	tmp[1] = NULL;
	tmp[3] = NULL;
	mlx_string_put(s->ig->mlx, s->ig->win, 10, 50, -1, "Mode : Object");
	if (s->objtab[s->target - 1]->objtp == SP)
	{
		pos = ((t_sp *)s->objtab[s->target - 1]->obj)->pos;
		tmp[0] = "[ O ] - Diameter + [ P ]";
		print_f(s, ((t_sp *)s->objtab[s->target - 1]->obj)->diameter, print_xyz(s, "Diameter", tmp, 155), 15);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Sphere");
	}
	if (s->objtab[s->target - 1]->objtp == PL)
	{
		pos = ((t_pl *)s->objtab[s->target - 1]->obj)->pos;
		print_v(s, ((t_pl *)s->objtab[s->target - 1]->obj)->rotate, print_xyz(s, "Orientation", rot, 155), 15);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Plan");
	}
	if (s->objtab[s->target - 1]->objtp == CY)
	{
		pos = ((t_cy *)s->objtab[s->target - 1]->obj)->pos;
		i = print_v(s, ((t_cy *)s->objtab[s->target - 1]->obj)->rotate, print_xyz(s, " Rotate ", rot, 155), 15);
		tmp[0] = "[ O ] - Diameter + [ P ]";
		i = print_f(s, ((t_cy *)s->objtab[s->target - 1]->obj)->diameter, print_xyz(s, "Diameter", tmp, i + 25), 15);
		tmp[0] = "[ U ] - Height + [ I ]";
		i = print_f(s, ((t_cy *)s->objtab[s->target - 1]->obj)->height, print_xyz(s, "Height", tmp, i + 25), 15);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Cylindre");
	}
	// if (s->objtab[s->target - 1]->objtp == 3)
	// 	t = "Cone";
	tmp[0] = "[ 4 ] - X + [ 6 ]";
	tmp[1] = "[ 7 ] - Y + [ 9 ]";
	tmp[2] = "[ 8 ] - Z + [ 2 ]";
	print_v(s, pos, print_xyz(s, "Translate", tmp, 65), 15);
}

void	put_debug_to_window(void *mlx, void *win, t_scene *s)
{
	char	*t;
	char	*trans[4];
	char	*rot[4];
	char	*tmp[4];
	int		i;

	mlx_string_put(mlx, win, 10, 10, -1, "MiniRT");
	mlx_string_put(mlx, win, 10, 25, -1, s->msg);
	trans[0] = "[ A ] - X + [ D ]";
	trans[1] = "[CTR] - Y + [SPACE]";
	trans[2] = "[ S ] - Z + [ W ]";
	trans[3] = NULL;
	rot[0] = "[right] - X + [left]";
	rot[1] = "[ down] - Y + [ up ]";
	rot[2] = "[  -  ] - Z + [  + ]";
	rot[3] = NULL;
	tmp[0] = NULL;
	tmp[1] = NULL;
	if (s->target == -1)
	{
		mlx_string_put(mlx, win, 10, 50, -1, "Mode : Camera");
		i = print_v(s, s->cam.translate, print_xyz(s, "Translate", trans, 65), 15);
		print_v(s, s->cam.rotate, print_xyz(s, "Rotate", rot, i + 20), 15);
	}
	else if (s->target == -2)
	{
		mlx_string_put(mlx, win, 10, 50, -1, "Mode : Light");
		if (s->target_light == -1)
			mlx_string_put(mlx, win, 10, 60, -1, "Select light by num keypad. From 0 (Ambient) to Number of light(s)");
		else if (s->target_light == 0)
		{
			tmp[0] = "[down] - Brightness + [up]";
			print_f(s, s->alight.al, print_xyz(s, "Ambient", tmp, 65), 15);
		}
		else
		{
			t = ft_itoa(s->target_light);
			mlx_string_put(mlx, win, 100, 50, -1, t);
			free(t);
			i = print_v(s, s->lamptab[s->target_light - 1]->pos, print_xyz(s, "Translate", trans, 65), 15);
			tmp[0] = "[down] - Brightness + [up]";
			print_f(s, s->lamptab[s->target_light - 1]->brightness, print_xyz(s, "Brightness", tmp, i + 20), 15);
		}
	}
	else if (s->target == 0)
		mlx_string_put(mlx, win, 10, 50, -1, "Mode : B G");
	else
		put_debug_to_window_obj(s, rot);
}