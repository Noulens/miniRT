/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:07:10 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/10 03:48:55 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "init.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
t_ray	build_camera_ray(t_scene *scene, int x, int y);
int		intersect_sphere(t_ray ray, t_stdobj *tmp, int k);
int		intersect_plane(t_ray ray, t_stdobj *tmp, int k);
int		render(t_scene *scn, t_func *inter);
void	win_launcher(t_scene *scn);

#endif
