/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:19:40 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/15 17:21:04 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include	<stdio.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<math.h>
# include	<fcntl.h>
# include   <stdlib.h>
# include "mlx.h"
# include "libft.h"
# define WINDOW_HEIGHT 1200
# define WINDOW_WIDTH 1600

typedef struct s_data{
    void	*mlx_ptr;
    void	*win_ptr;
    void	*img;
    int		win_w;
    int		win_h;
    char	*addr;
    int		bpp;
    int		linel;
    int		endian;
    float	edgel;
}	t_data;

#endif
