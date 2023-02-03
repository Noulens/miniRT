/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_win_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 08:05:32 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/02 17:02:55 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

void	free_four_str(char *a, char *b, char *c, char *d)
{
	free(a);
	free(b);
	free(c);
	free(d);
}

char	*vec_to_string(t_vec3 vec)
{
	char	*x;
	char	*y;
	char	*z;
	char	*tmp;
	char	*ret;

	x = ft_ftoa(vec.x, 3);
	if (!x)
		return (NULL);
	y = ft_ftoa(vec.y, 3);
	if (!y)
		return (free(x), NULL);
	z = ft_ftoa(vec.z, 3);
	if (!z)
		return (free(x), free(y), NULL);
	tmp = ft_strjoinsep(x, y, " ");
	if (!tmp)
		return (free(x), free(y), free(z), NULL);
	ret = ft_strjoinsep(tmp, z, " ");
	if (!ret)
		return (free_four_str(x, y, z, tmp), NULL);
	free_four_str(x, y, z, tmp);
	return (ret);
}

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
	if (!tmp)
		return (-1);
	ret = ft_strjoinsep(tmp, str, " ");
	if (!ret)
		return (free(tmp), -1);
	mlx_string_put(s->ig->mlx, s->ig->win, 10, a, -1, ret);
	free(ret);
	free(tmp);
	i = -1;
	while (inst[++i])
		mlx_string_put(s->ig->mlx, s->ig->win, \
		10, a + (gap * (i + 1)), -1, inst[i]);
	return (a + (gap * i));
}

int	ft_mlx_vec_out(t_scene *s, int i, char *param, char *inst[4])
{
	char	*str;
	int		a;
	int		gap;

	gap = 15;
	str = vec_to_string(s->norminettev);
	if (!str)
		return (-1);
	a = ft_mlx_inst_out(s, param, inst, i);
	if (a == -1)
		return (free(str), -1);
	mlx_string_put(s->ig->mlx, s->ig->win, 30, a + gap, -1, str);
	free(str);
	return (a + gap);
}

int	ft_mlx_float_out(t_scene *s, int i, char *param, char *inst)
{
	char	*str;
	int		gap;
	int		a;
	char	*new_inst[4];

	new_inst[0] = inst;
	new_inst[1] = NULL;
	gap = 15;
	str = ft_ftoa(s->norminettef, 1);
	if (!str)
		return (-1);
	a = ft_mlx_inst_out(s, param, new_inst, i);
	if (a == -1)
		return (free(str), -1);
	mlx_string_put(s->ig->mlx, s->ig->win, 30, a + gap, -1, str);
	free(str);
	return (a + gap);
}
