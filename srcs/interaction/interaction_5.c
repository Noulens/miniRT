/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:13:43 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/01 18:09:35 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

char	*get_float(int precision, float a)
{
	char	*flo;
	int		i;
	char	*ret;

	i = -1;
	flo = malloc(sizeof(char) * precision + 1);
	if (!flo)
		return (NULL);
	flo[precision] = '\0';
	a = a - (int)a;
	while (++i < precision)
	{
		a *= 10;
		flo[i] = 0 + '0';
		if ((int)a != 0)
		{
			ret = ft_itoa(a);
			flo[i] = ret[0];
			if (a < 0)
				flo[i] = ret[1];
			free(ret);
			a = a - (int)a;
		}
	}
	return (flo);
}

char	*get_int(float a)
{
	char	*integer;
	char	*ret;

	ret = NULL;
	if (a < 0 && a > -1)
	{
		ret = ft_itoa((int)a);
		integer = ft_strjoin("-", ret);
		if (!integer)
			return (free(ret), NULL);
		free(ret);
	}
	else
	{
		integer = ft_itoa((int)a);
		if (!integer)
			return (free(ret), NULL);
	}
	return (integer);
}

char	*ft_ftoa(float a, int precision)
{
	char	*integer;
	char	*flo;
	char	*ret;

	ret = NULL;
	integer = get_int(a);
	if (!integer)
		return (NULL);
	flo = get_float(precision, a);
	if (!flo)
		return (free(integer), NULL);
	ret = ft_strjoinsep(integer, flo, ".");
	if (!ret)
		return (free(integer), free(flo), NULL);
	return (free(integer), free(flo), ret);
}

void	do_transform_light(int keycode, t_scene *scene)
{
	t_light	*light;

	light = scene->lamptab[scene->target_light - 1];
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
	keep_between_zero_one(&light->brightness);
}

int	find_light(t_scene *s, int keycode)
{
	int	num[10];
	int	i;

	num[0] = NUMPAD_0;
	num[1] = NUMPAD_1;
	num[2] = NUMPAD_2;
	num[3] = NUMPAD_3;
	num[4] = NUMPAD_4;
	num[5] = NUMPAD_5;
	num[6] = NUMPAD_6;
	num[7] = NUMPAD_7;
	num[8] = NUMPAD_8;
	num[9] = NUMPAD_9;
	i = 0;
	if (keycode == NUMPAD_0)
		return (0);
	while (++i <= s->num_lamps)
	{
		if (num[i] == keycode)
			return (i);
	}
	return (-1);
}
