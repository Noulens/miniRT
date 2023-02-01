/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:47:21 by waxxy             #+#    #+#             */
/*   Updated: 2023/02/01 09:54:47 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct s_invert
{
	int			i;
	int			j;
	int			k;
	int			l;
	int			m;
	int			n;
	int			o;
	int			p;
	int			q;
	int			r;
	int			pivot;
	float		pivotsize;
	float		tmp;
	float		f;
	float		divisor;
	float		constant;
}	t_inv;

typedef enum e_quad
{
	A,
	B,
	C,
	DELTA,
	ROOT1,
	ROOT2,
	RES
}	t_quadratic;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
	float	t;
}	t_vec3;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_inter_c
{
	t_vec3	v[8];
	float	quad[9];
	t_ray	*raycap;
	float	*dist;
}	t_inter_c;

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
	CO
}	t_objtp;

typedef enum e_mat
{
	T,
	RX,
	RY,
	RZ,
}	t_mat;

typedef struct s_surfaceinfo
{
	t_vec3	hit_point;
	t_vec3	view_dir;
	t_vec3	hit_normal;
	t_vec3	hit_uv;
	float	hit_dist;
}	t_surfaceinfo;

typedef struct s_material
{
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	t_vec3	result;
	t_vec3	obj_color;
	float	face_ratio;
	int		vis;
	float	l_inten;
	t_vec3	l_dir;
}	t_material;

typedef struct s_stdobj
{
	void			*obj;
	t_objtp			objtp;
	int				objid;
	int				metacolor;
	struct s_stdobj	*next;
}	t_stdobj;

typedef struct s_plan
{
	t_vec3	pos;
	t_vec3	orientation;
	t_vec3	translate;
	t_vec3	rotate;
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	hit_normal;
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
	t_vec3			pos;
	t_vec3			translate;
	t_vec3			rotate;
	int				color;
	float			diameter;
	float			radius;
}	t_sp;

typedef struct s_co
{
	t_vec3	pos;
	t_vec3	orientation;
	t_vec3	translate;
	t_vec3	rotate;
	int		color;
	float	height;
	float	rad;
}	t_co;

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
	t_vec3			pos;
	t_vec3			translate;
	t_vec3			rotate;
	int				color;
	float			brightness;
	float			exposure;
	int				idl;
	struct s_light	*next;
}	t_light;

typedef struct s_alight
{
	float	al;
	int		color;
}	t_alight;

typedef int	(*t_func[4])(t_ray ms, t_stdobj *inter, float *hit_distance);

typedef struct s_scene
{
	t_stdobj	**objtab;
	t_stdobj	*objects;
	t_light		**lamptab;
	t_light		*lamp;
	t_img		*ig;
	t_func		*func_ptr;
	t_alight	alight;
	t_matrix4	fwtfm;
	t_cam		cam;
	float		image_ratio;
	int			win_w;
	int			win_h;
	int			x;
	int			y;
	int			k;
	int			target;
	int			target_light;
	int			num_objects_in_scene;
	int			num_lamps;
	int			bg_color;
	t_vec3		norminettev;
	float		norminettef;
	char		*msg;
}	t_scene;

#endif
