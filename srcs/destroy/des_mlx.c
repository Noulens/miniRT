/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:18:20 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/15 20:18:23 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destroy.h"

void	des_mlx(void *mlx, void *img, void *win)
{
	mlx_destroy_image(mlx, img);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
	free(mlx);
}

void	des_minirt(t_scene *scn)
{
	objclear(scn->objects);
	if (scn->objtab)
		free(scn->objtab);
}
