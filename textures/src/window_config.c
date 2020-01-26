/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:50:58 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/25 16:41:29 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	open_win(t_params *params)
{
	params->mlx = mlx_init();
	params->window = mlx_new_window(params->mlx,
			params->info->scren_with, params->info->scren_height
			, "cub3D");
}
