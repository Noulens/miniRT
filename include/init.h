/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:18:53 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/21 16:02:48 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "mlx.h"
# include "libft.h"
# include "colors.h"
# include "tools.h"
# include "math_func.h"
# include "interaction.h"
# include "parsing.h"

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
	t_scene	*scene;
}	t_img;

t_scene scene_init(t_scene *s);

#endif
