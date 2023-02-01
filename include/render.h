/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:07:10 by waxxy             #+#    #+#             */
/*   Updated: 2023/02/01 08:19:35 by hyunah           ###   ########.fr       */
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
void			get_pointl_info(t_scene *s, t_surfaceinfo *i, t_vec3 *d, \
float *f);
int				shadow_vis(t_scene *s, t_func *f, t_surfaceinfo *i, t_vec3 d);
int				isacap(t_cy *cyl, t_inter_c *ic, t_pl *cap, t_stdobj *capper);
void			hit_normal_sphere(t_surfaceinfo *info, t_stdobj *obj);
void			hit_normal_plane(t_surfaceinfo *info, t_pl *pl);
void			hit_normal_cyl(t_surfaceinfo *info, t_stdobj *obj);
void			hit_normal_co(t_surfaceinfo *info, t_stdobj *obj);
int				intersect_plane_new(t_ray r, t_stdobj *t, float *hit);
t_vec3			calcule_uv_point_plane(t_pl *pl, t_surfaceinfo *info);
void			get_render_info(t_scene *s, t_surfaceinfo *i, \
int c, t_material *m);
void			keep_between_zero_one_vector(t_vec3 *v);

#endif
