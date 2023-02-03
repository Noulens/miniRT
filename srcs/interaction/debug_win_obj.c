/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_win_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:25:38 by hyujung           #+#    #+#             */
/*   Updated: 2023/02/02 19:45:10 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

int	put_debug_to_window_co(t_scene *s, char *rot[4], t_vec3 *pos)
{
	(void) rot;
	*pos = ((t_co *)s->objtab[s->target - 1]->obj)->pos;
	mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Cone");
	mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Cone");
	return (0);
}

int	put_debug_to_window_cy_co(t_scene *s, char *rot[4], t_vec3 *pos)
{
	int		i;

	if (s->objtab[s->target - 1]->objtp == CY)
	{
		*pos = ((t_cy *)s->objtab[s->target - 1]->obj)->pos;
		s->norminettev = ((t_cy *)s->objtab[s->target - 1]->obj)->orientation;
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Cylindre");
		i = ft_mlx_vec_out(s, 155, " Orientation ", rot);
		if (i == -1)
			return (1);
		s->norminettef = ((t_cy *)s->objtab[s->target - 1]->obj)->diameter;
		i = ft_mlx_float_out(s, i + 20, "Diameter", "[ O ] - Diameter + [ P ]");
		if (i == -1)
			return (1);
		s->norminettef = ((t_cy *)s->objtab[s->target - 1]->obj)->height;
		i = ft_mlx_float_out(s, i + 20, "Height", "[ U ] - Height + [ I ]");
		if (i == -1)
			return (1);
	}
	else if (BONUS == 1 && s->objtab[s->target - 1]->objtp == CO)
		put_debug_to_window_co(s, rot, pos);
	return (0);
}

int	put_debug_to_window_sp_pl(t_scene *s, char *rot[4], t_vec3 *pos)
{
	if (s->objtab[s->target - 1]->objtp == SP)
	{
		pos->x = ((t_sp *)s->objtab[s->target - 1]->obj)->pos.x;
		pos->y = ((t_sp *)s->objtab[s->target - 1]->obj)->pos.y;
		pos->z = ((t_sp *)s->objtab[s->target - 1]->obj)->pos.z;
		s->norminettef = ((t_sp *)s->objtab[s->target - 1]->obj)->diameter;
		if (ft_mlx_float_out(s, 155, "Diameter", \
		"[ O ] - Diameter + [ P ]") == -1)
			return (1);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Sphere");
	}
	else if (s->objtab[s->target - 1]->objtp == PL)
	{
		pos->x = ((t_pl *)s->objtab[s->target - 1]->obj)->translate.x;
		pos->y = ((t_pl *)s->objtab[s->target - 1]->obj)->translate.y;
		pos->z = ((t_pl *)s->objtab[s->target - 1]->obj)->translate.z;
		s->norminettev = ((t_pl *)s->objtab[s->target - 1]->obj)->rotate;
		if (ft_mlx_vec_out(s, 155, "Rotation", rot) == -1)
			return (1);
		mlx_string_put(s->ig->mlx, s->ig->win, 100, 50, -1, "Plan");
	}
	return (0);
}

int	put_debug_to_window_obj(t_scene *s, char *rot[4])
{
	t_vec3	pos;
	char	*inst[4];
	int		error;

	error = 0;
	mlx_string_put(s->ig->mlx, s->ig->win, 10, 50, -1, "Mode : Object");
	if (s->objtab[s->target - 1]->objtp == SP || \
	s->objtab[s->target - 1]->objtp == PL)
	{
		if (put_debug_to_window_sp_pl(s, rot, &pos))
			return (1);
	}
	else
	{
		if (put_debug_to_window_cy_co(s, rot, &pos))
			return (1);
	}
	init_instructions((inst), "[  4  ] - X + [  6  ]", \
	"[  2  ] - Y + [  8  ]", "[  9  ] - Z + [  7  ]");
	s->norminettev = pos;
	error = ft_mlx_vec_out(s, 65, "Translate", inst);
	if (error == -1)
		return (1);
	return (0);
}

void	round_ori(t_vec3 *ori)
{
	if (ori->y <= 0.1f && ori->y >= -0.1)
		ori->y = 0;
	if (ori->y >= 0.90f && ori->y <= 1.1)
		ori->y = 1;
	if (ori->x <= 0.1f && ori->x >= -0.1)
		ori->x = 0;
	if (ori->x >= 0.9f && ori->x <= 1.1)
		ori->x = 1;
	if (ori->z <= 0.1f && ori->z >= -0.1)
		ori->z = 0;
	if (ori->z >= 0.9f && ori->z <= 1.1)
		ori->z = 1;
}
