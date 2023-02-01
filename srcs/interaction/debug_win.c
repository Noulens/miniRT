/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 02:10:03 by  hyunah           #+#    #+#             */
/*   Updated: 2023/02/01 19:02:02 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	init_instructions(char *inst[4], char *x, char *y, char *z)
{
	(inst)[0] = x;
	(inst)[1] = y;
	(inst)[2] = z;
	(inst)[3] = NULL;
}

int	put_debug_to_window_spotl(t_scene *s, char *trans[4])
{
	char	*t;
	int		i;

	t = ft_itoa(s->target_light);
	if (!t)
		return (1);
	mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, t);
	free(t);
	s->norminettev = s->lamptab[s->target_light - 1]->pos;
	i = ft_mlx_vec_out(s, 65, "Translate", trans);
	if (i == -1)
		return (1);
	s->norminettef = s->lamptab[s->target_light - 1]->brightness;
	i = ft_mlx_float_out(s, i + 20, "Brightness", "[down] - Brightness + [up]");
	if (i == -1)
		return (1);
	return (0);
}

int	put_debug_to_window_light(t_scene *s, char *trans[4])
{
	mlx_string_put(s->ig->mlx, s->ig->win, 10, 50, -1, "Mode : Light");
	if (s->target_light == -1)
		mlx_string_put(s->ig->mlx, s->ig->win, 10, 60, -1, \
		"Select light by num keypad. From 0 (Ambient) to Number of light(s)");
	else if (s->target_light == 0)
	{
		s->norminettef = s->alight.al;
		if (ft_mlx_float_out(s, 65, "Ambient", \
		"[down] - Brightness + [up]") == -1)
			return (1);
	}
	else
	{
		if (put_debug_to_window_spotl(s, trans))
			return (1);
	}
	return (0);
}

int	put_debug_to_window_cam(t_scene *s, char *inst[2][4])
{
	int	i;

	i = 0;
	mlx_string_put(s->ig->mlx, s->ig->win, 10, 50, -1, "Mode : Camera");
	s->norminettev = s->cam.translate;
	i = ft_mlx_vec_out(s, 65, "Translate", inst[0]);
	if (i == -1)
		return (1);
	s->norminettev = s->cam.rotate;
	if (ft_mlx_vec_out(s, i + 20, "Rotate", inst[1]) == -1)
		return (1);
	return (0);
}

int	put_debug_to_window(void *mlx, void *win, t_scene *s)
{
	char	*inst[2][4];
	int		error;

	error = 0;
	mlx_string_put(mlx, win, 10, 10, -1, "MiniRT");
	mlx_string_put(mlx, win, 10, 25, -1, s->msg);
	init_instructions((inst[0]), "[  A  ] - X + [  D  ]", \
	"[ CTR ] - Y + [SPACE]", "[  S  ] - Z + [  W  ]");
	init_instructions((inst[1]), "[right] - X + [ left]", \
	"[ down] - Y + [  up ]", "[  -  ] - Z + [  +  ]");
	if (s->target == -1)
		error = put_debug_to_window_cam(s, inst);
	else if (s->target == -2)
		error = put_debug_to_window_light(s, inst[0]);
	else if (s->target == -3)
		mlx_string_put(mlx, win, 10, 50, -1, "Mode : B G");
	else
		error = put_debug_to_window_obj(s, inst[1]);
	if (error)
		return (1);
	return (0);
}
