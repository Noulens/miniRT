/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:47:21 by waxxy             #+#    #+#             */
/*   Updated: 2022/12/28 17:47:23 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_data
{
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_matrix4
{
	float	m[4][4];
}	t_matrix4;

typedef enum e_obj
{
	SP,
	CY,
	PL,
	HY,
	CO
}	t_objtp;

typedef struct s_stdobj
{
	void			*obj;
	t_objtp			objtp;
	int 			objid;
	struct s_stdobj	*next;
}	t_stdobj;

typedef struct s_plan
{
	t_vec3	pos;
	t_vec3	orientation;
	t_vec3	translate;
	t_vec3	rotate;
	int		color;
}	t_pl;

typedef struct s_cy
{
	t_vec3	pos;
	t_vec3	orientation;
	t_vec3	translate;
	t_vec3	rotate;
	int		color;
	float	height;
	float	diameter;
}	t_cy;

typedef struct s_sp
{
	t_vec3	pos;
	t_vec3	translate;
	int		color;
	float	diameter;
}	t_sp;

typedef struct s_cam
{
	t_vec3	pos;
	t_vec3	translate;
	t_vec3	rotate;
	t_vec3	orientation;
	float	fov_w;
	float	fov_h;
	float	fov_h_len;
	float	focal_length;
}	t_cam;

typedef struct s_light
{
	t_vec3	pos;
	t_vec3	translate;
	t_vec3	rotate;
	int		color;
	float	brightness;
}	t_light;

typedef struct s_alight
{
	float	al;
	int		color;
}	t_alight;

typedef struct s_scene
{
	int			win_w;
	int			win_h;
	float		image_ratio;
	int			num_objects_in_scene;
	t_light		light;
	t_alight	alight;
	t_stdobj	*objects;
	t_cam		cam;
	int			bg_color;
	t_img		*ig;
	int			target;
}	t_scene;

#endif
