/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:10:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/26 08:27:02 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	put_debug_to_window_light(t_scene *s, char *trans[4])
{
	char	*inst[4];
	char	*t;
	int		i;

	inst[1] = NULL;
	mlx_string_put(s->ig->mlx, s->ig->win, 10, 50, -1, "Mode : Light");
	if (s->target_light == -1)
		mlx_string_put(s->ig->mlx, s->ig->win, 10, 60, -1, \
		"Select light by num keypad. From 0 (Ambient) to Number of light(s)");
	else if (s->target_light == 0)
	{
		inst[0] = "[down] - Brightness + [up]";
		ft_mlx_float_out(s, s->alight.al, ft_mlx_inst_out(s, "Ambient", inst, 65), 15);
	}
	else
	{
		t = ft_itoa(s->target_light);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, t);
		free(t);
		inst[0] = "[down] - Brightness + [up]";
		i = ft_mlx_vec_out(s, s->lamptab[s->target_light - 1]->pos, ft_mlx_inst_out(s, "Translate", trans, 65), 15);
		ft_mlx_float_out(s, s->lamptab[s->target_light - 1]->brightness, ft_mlx_inst_out(s, "Brightness", inst, i + 20), 15);
	}
}

void	put_debug_to_window_obj(t_scene *s, char *rot[4])
{
	t_vec3	pos;
	int		i;
	char	*inst[4];

	inst[1] = NULL;
	inst[3] = NULL;
	mlx_string_put(s->ig->mlx, s->ig->win, 10, 50, -1, "Mode : Object");
	if (s->objtab[s->target - 1]->objtp == SP)
	{
		pos = ((t_sp *)s->objtab[s->target - 1]->obj)->pos;
		inst[0] = "[ O ] - Diameter + [ P ]";
		ft_mlx_float_out(s, ((t_sp *)s->objtab[s->target - 1]->obj)->diameter, ft_mlx_inst_out(s, "Diameter", inst, 155), 15);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Sphere");
	}
	else if (s->objtab[s->target - 1]->objtp == PL)
	{
		pos = ((t_pl *)s->objtab[s->target - 1]->obj)->pos;
		ft_mlx_vec_out(s, ((t_pl *)s->objtab[s->target - 1]->obj)->rotate, ft_mlx_inst_out(s, "Orientation", rot, 155), 15);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Plan");
	}
	else if (s->objtab[s->target - 1]->objtp == CY)
	{
		pos = ((t_cy *)s->objtab[s->target - 1]->obj)->pos;
		i = ft_mlx_vec_out(s, ((t_cy *)s->objtab[s->target - 1]->obj)->rotate, ft_mlx_inst_out(s, " Rotate ", rot, 155), 15);
		inst[0] = "[ O ] - Diameter + [ P ]";
		i = ft_mlx_float_out(s, ((t_cy *)s->objtab[s->target - 1]->obj)->diameter, ft_mlx_inst_out(s, "Diameter", inst, i + 25), 15);
		inst[0] = "[ U ] - Height + [ I ]";
		i = ft_mlx_float_out(s, ((t_cy *)s->objtab[s->target - 1]->obj)->height, ft_mlx_inst_out(s, "Height", inst, i + 25), 15);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Cylindre");
	}
	// else if (s->objtab[s->target - 1]->objtp == 3)
	// 	t = "Cone";
	inst[0] = "[ 4 ] - X + [ 6 ]";
	inst[1] = "[ 7 ] - Y + [ 9 ]";
	inst[2] = "[ 8 ] - Z + [ 2 ]";
	ft_mlx_vec_out(s, pos, ft_mlx_inst_out(s, "Translate", inst, 65), 15);
}

void	put_debug_to_window(void *mlx, void *win, t_scene *s)
{
	char	*inst[2][4];
	int		i;

	mlx_string_put(mlx, win, 10, 10, -1, "MiniRT");
	mlx_string_put(mlx, win, 10, 25, -1, s->msg);
	inst[0][0] = "[ A ] - X + [ D ]";
	inst[0][1] = "[CTR] - Y + [SPACE]";
	inst[0][2] = "[ S ] - Z + [ W ]";
	inst[0][3] = NULL;
	inst[1][0] = "[right] - X + [left]";
	inst[1][1] = "[ down] - Y + [ up ]";
	inst[1][2] = "[  -  ] - Z + [  + ]";
	inst[1][3] = NULL;
	if (s->target == -1)
	{
		mlx_string_put(mlx, win, 10, 50, -1, "Mode : Camera");
		i = ft_mlx_vec_out(s, s->cam.translate, ft_mlx_inst_out(s, "Translate", inst[0], 65), 15);
		ft_mlx_vec_out(s, s->cam.rotate, ft_mlx_inst_out(s, "Rotate", inst[1], i + 20), 15);
	}
	else if (s->target == -2)
		put_debug_to_window_light(s, inst[0]);
	else if (s->target == 0)
		mlx_string_put(mlx, win, 10, 50, -1, "Mode : B G");
	else
		put_debug_to_window_obj(s, inst[1]);
}