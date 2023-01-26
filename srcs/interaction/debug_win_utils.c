/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_win_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 08:05:32 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/26 08:31:11 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

int	ft_mlx_inst_out(t_scene *s, char *param, char *inst[4], int a)
{
	int		gap;
	int		i;
	char	*str;
	char	*ret;
	char	*tmp;

	gap = 15;
	str = "----";
	tmp = ft_strjoinsep(str, param, " ");
	ret = ft_strjoinsep(tmp, str, " ");
	mlx_string_put(s->ig->mlx, s->ig->win, 10, a, -1, ret);
	free(ret);
	free(tmp);
	i = -1;
	while (inst[++i])
		mlx_string_put(s->ig->mlx, s->ig->win, \
		10, a + (gap * (i + 1)), -1, inst[i]);
	return (a + (gap * i));
}

int	ft_mlx_vec_out(t_scene *s, t_vec3 v, int i, int gap)
{
	char	*str;

	str = vec_to_string(v);
	mlx_string_put(s->ig->mlx, s->ig->win, 30, i + gap, -1, str);
	free(str);
	return (i + gap);
}

int	ft_mlx_float_out(t_scene *s, float f, int i, int gap)
{
	char	*str;

	str = ft_ftoa(f, 1);
	mlx_string_put(s->ig->mlx, s->ig->win, 30, i + gap, -1, str);
	free(str);
	return (i + gap);
}