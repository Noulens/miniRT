/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:47:21 by waxxy             #+#    #+#             */
/*   Updated: 2023/01/13 09:26:34 by hyunah           ###   ########.fr       */
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
	float	hit_dist;
}	t_surfaceinfo;

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
	float	diameter;
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

typedef int	(*t_func[4])(t_ray ms, t_stdobj *inter, float *hit_distance);

typedef struct s_scene
{
	int			win_w;
	int			win_h;
	float		image_ratio;
	int			num_objects_in_scene;
	t_light		light;
	t_alight	alight;
	t_stdobj	*objects;
	t_stdobj	**objtab;
	t_cam		cam;
	int			bg_color;
	t_img		*ig;
	int			target;
	t_func		*func_ptr;
	t_matrix4	fwtfm;
	t_matrix4	bcktfm;
}	t_scene;

#endif
