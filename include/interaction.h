/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:21:14 by hyunah            #+#    #+#             */
/*   Updated: 2022/12/21 12:54:45 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTION_H
# define INTERACTION_H
# define KEY_ESC 65307
# define KEY_A 97

# include "init.h"
# include "destroy.h"

int	ft_closebutton(void *param);
int	ft_key(int keycode, void *img);

#endif
