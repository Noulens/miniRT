/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:13:43 by hyunah            #+#    #+#             */
/*   Updated: 2023/01/26 00:07:01 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

char *ft_ftoa(float a, int precision)
{
	int		i;
	char	*integer;
	char	*flo;
	char	*ret;

	ret = NULL;
	i = -1;
	integer = ft_itoa((int)a);
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
	ret = ft_strjoinsep(integer, flo, ".");
	return (free(integer), free(flo), ret);
}

char	*vec_to_string(t_vec3 vec)
{
	char	*x;
	char	*y;
	char	*z;
	char	*tmp;
	char	*ret;

	x = ft_ftoa(vec.x, 3);
	y = ft_ftoa(vec.y, 3);
	z = ft_ftoa(vec.z, 3);
	tmp = ft_strjoinsep(x, y, " ");
	ret = ft_strjoinsep(tmp, z, " ");
	free(x);
	free(y);
	free(z);
	free(tmp);
	return (ret);
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
	if (light->brightness >= 1)
		light->brightness = 1;
	if (light->brightness <= 0)
		light->brightness = 0;
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
	if (scene->target_light == 0)
	{
		if (keycode == KEY_UP)
			scene->alight.al += 0.1f;
		if (keycode == KEY_DOWN)
			scene->alight.al -= 0.1f;
		if (scene->alight.al <= 0)
			scene->alight.al = 0;
	}
	else if (scene->target_light != -1)
		do_transform_light(keycode, scene);
	else
		ft_printf("target is -1\n");
	return (1);
}
