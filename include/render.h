/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:07:10 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/23 16:44:48 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "init.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
t_ray	build_camera_ray(t_scene *scene, int x, int y);
int		intersect(t_ray ray, t_scene *scene);
int		render(t_scene *scn);
void	win_launcher(t_scene *scn);

#endif
