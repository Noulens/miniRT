/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:18:36 by tnoulens          #+#    #+#             */
/*   Updated: 2022/12/15 20:18:38 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTROY_H
# define DESTROY_H

# include "mlx.h"
# include "libft.h"
# include "colors.h"
# include "parsing.h"
# include "tools.h"
# include "struct.h"

void	des_mlx(void *mlx, void *img, void *win);
void	des_minirt(t_scene *scn);

#endif
