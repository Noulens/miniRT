/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:07:10 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/12 16:38:57 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "init.h"

void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
t_ray			build_camera_ray(t_scene *scene, int x, int y);
int				intersect_sphere(t_ray ray, t_stdobj *tmp, float *hit_distance);
int				intersect_plane(t_ray ray, t_stdobj *tmp, float *hit_distance);
int				intersect_cylinder(t_ray ray, t_stdobj *cy_std, float *dist);
int				render(t_scene *scn, t_func *inter);
void			win_launcher(t_scene *scn);
int				compute_pixel(t_scene *scene, int i, int j, t_func *inter);
void			clear_image(t_scene *scene);
t_surfaceinfo	*get_surfaceinfo(t_surfaceinfo *info, t_stdobj *obj, t_ray ray);
int				lambert(t_scene *s, t_surfaceinfo *info, int obj, t_func *i);
int				find_closest_obj(t_scene *s, t_ray ray, t_func *i, float *d);

#endif
