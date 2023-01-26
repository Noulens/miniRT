/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 23:10:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/26 09:46:17 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	put_debug_to_window_light(t_scene *s, char *trans[4])
{
	char	*t;
	int		i;

	mlx_string_put(s->ig->mlx, s->ig->win, 10, 50, -1, "Mode : Light");
	if (s->target_light == -1)
		mlx_string_put(s->ig->mlx, s->ig->win, 10, 60, -1, \
		"Select light by num keypad. From 0 (Ambient) to Number of light(s)");
	else if (s->target_light == 0)
	{
		s->norminettef = s->alight.al;
		ft_mlx_float_out(s, 65, "Ambient", "[down] - Brightness + [up]");
	}
	else
	{
		t = ft_itoa(s->target_light);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, t);
		free(t);
		s->norminettev = s->lamptab[s->target_light - 1]->pos;
		i = ft_mlx_vec_out(s, 65, "Translate", trans);
		s->norminettef = s->lamptab[s->target_light - 1]->brightness;
		ft_mlx_float_out(s, i + 20, "Brightness", "[down] - Brightness + [up]");
	}
}

void	put_debug_to_window_obj(t_scene *s, char *rot[4])
{
	t_vec3	pos;
	int		i;
	char	*inst[4];

	mlx_string_put(s->ig->mlx, s->ig->win, 10, 50, -1, "Mode : Object");
	if (s->objtab[s->target - 1]->objtp == SP)
	{
		pos = ((t_sp *)s->objtab[s->target - 1]->obj)->pos;
		s->norminettef = ((t_sp *)s->objtab[s->target - 1]->obj)->diameter;
		ft_mlx_float_out(s, 155, "Diameter", "[ O ] - Diameter + [ P ]");
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Sphere");
	}
	else if (s->objtab[s->target - 1]->objtp == PL)
	{
		pos = ((t_pl *)s->objtab[s->target - 1]->obj)->pos;
		s->norminettev = ((t_pl *)s->objtab[s->target - 1]->obj)->rotate;
		ft_mlx_vec_out(s, 155, "Orientation", rot);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Plan");
	}
	else if (s->objtab[s->target - 1]->objtp == CY)
	{
		pos = ((t_cy *)s->objtab[s->target - 1]->obj)->pos;
		s->norminettev = ((t_cy *)s->objtab[s->target - 1]->obj)->rotate;
		i = ft_mlx_vec_out(s, 155, " Rotate ", rot);
		s->norminettef = ((t_cy *)s->objtab[s->target - 1]->obj)->diameter;
		i = ft_mlx_float_out(s, i + 20, "Diameter", "[ O ] - Diameter + [ P ]");
		s->norminettef = ((t_cy *)s->objtab[s->target - 1]->obj)->height;
		i = ft_mlx_float_out(s, i + 20, "Height", "[ U ] - Height + [ I ]");
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Cylindre");
	}
	// else if (s->objtab[s->target - 1]->objtp == 3)
	// 	t = "Cone";
	inst[0] = "[  4  ] - X + [  6  ]";
	inst[1] = "[  7  ] - Y + [  9  ]";
	inst[2] = "[  8  ] - Z + [  2  ]";
	inst[3] = NULL;
	s->norminettev = pos;
	ft_mlx_vec_out(s, 65, "Translate", inst);
}

void	put_debug_to_window(void *mlx, void *win, t_scene *s)
{
	char	*inst[2][4];
	int		i;

	mlx_string_put(mlx, win, 10, 10, -1, "MiniRT");
	mlx_string_put(mlx, win, 10, 25, -1, s->msg);
	inst[0][0] = "[  A  ] - X + [  D  ]";
	inst[0][1] = "[ CTR ] - Y + [SPACE]";
	inst[0][2] = "[  S  ] - Z + [  W  ]";
	inst[0][3] = NULL;
	inst[1][0] = "[right] - X + [left]";
	inst[1][1] = "[ down] - Y + [ up ]";
	inst[1][2] = "[  -  ] - Z + [  + ]";
	inst[1][3] = NULL;
	if (s->target == -1)
	{
		mlx_string_put(mlx, win, 10, 50, -1, "Mode : Camera");
		s->norminettev = s->cam.translate;
		i = ft_mlx_vec_out(s, 65, "Translate", inst[0]);
		s->norminettev = s->cam.rotate;
		ft_mlx_vec_out(s, i + 20, "Rotate", inst[1]);
	}
	else if (s->target == -2)
		put_debug_to_window_light(s, inst[0]);
	else if (s->target == 0)
		mlx_string_put(mlx, win, 10, 50, -1, "Mode : B G");
	else
		put_debug_to_window_obj(s, inst[1]);
}