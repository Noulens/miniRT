/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:34:48 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/21 12:55:17 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interaction.h"

int	ft_closebutton(void *param)
{
	t_img	*img;

	img = (t_img *)param;
	des_mlx(img->mlx, img->img, img->win);
	exit(0);
}

// int	ft_test(void *param)
// {
// 	t_img	*img;

// 	img = (t_img *)param;
// 	matrix_transformation(&cam->pos, cam->translate, cam->rotate);

// 	return (0);
// }

int	ft_key(int keycode, void *img)
{
	if (keycode == KEY_ESC)
		ft_closebutton(img);
	// if (keycode == KEY_A)
	// 	ft_test((void*)img);
	// printf("%i\n", keycode);
	return (0);
}