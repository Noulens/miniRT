/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:48 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/19 11:36:46 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "destroy.h"
#include "interaction.h"

int	ft_closebutton(void *param)
{
	t_img	*img;

	img = (t_img *)param;
	des_mlx(img->mlx, img->img, img->win);
	exit(0);
}

int	ft_key(int keycode, t_img *img)
{
	if (keycode == KEY_ESC)
		ft_closebutton((void *)img);
	return (0);
}