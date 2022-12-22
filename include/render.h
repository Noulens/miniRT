/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:07:10 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/21 12:47:03 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "init.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
t_ray	build_camera_ray(t_scene *scene, int x, int y);
int		interset(t_ray ray, t_scene *scene);
void	compute_pixel(t_scene *scene, t_vec3 *framebuffer, int i, int j);
int		render(t_img *img, t_scene *scene);
void    win_launcher(void);

#endif

