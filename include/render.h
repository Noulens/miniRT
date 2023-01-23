/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:07:10 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/23 14:58:52 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "init.h"

void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
void			win_launcher(t_scene *scn);
void			clear_image(t_scene *scene);
int				intersect_sphere(t_ray ray, t_stdobj *tmp, float *hit_distance);
int				intersect_plane(t_ray ray, t_stdobj *tmp, float *hit_distance);
int				intersect_cylinder(t_ray ray, t_stdobj *cy_std, float *dist);
int				intersect_cone(t_ray ray, t_stdobj *obj, float *dist);
int				render(t_scene *scn, t_func *inter);
int				compute_pixel(t_scene *scene, int i, int j, t_func *inter);
int				shading(t_scene *s, t_surfaceinfo *info, int obj, t_func *i);
int				find_closest_obj(t_scene *s, t_ray ray, t_func *i, float *d);
int				int_color(t_vec3 color);
t_vec3			vec_color(int color);
t_ray			build_camera_ray(t_scene *scene, int x, int y);
t_ray			build_camera_ray(t_scene *scene, int x, int y);
t_surfaceinfo	*get_surfaceinfo(t_surfaceinfo *info, t_stdobj *obj, t_ray ray);
void			init_disk(t_cy *cyl, t_vec3 *v, t_pl *cap, t_stdobj *capper);
float			getdouble(t_ray *ray, const float *dist, const t_pl cap);
void			get_inter_proj(t_ray *ray, t_vec3 *v, const float *quad);
void			get_pointlight_info(t_scene *s, t_surfaceinfo *i, t_vec3 *dir, float *f, int k);
int				shadow_visibility(t_scene *s, t_func *inter, t_surfaceinfo *i, t_vec3 ldir);

#endif
