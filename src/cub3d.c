/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:44:40 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 02:20:59 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mlx(t_params *params)
{
	mlx_hook(params->window, 2, 0, presskey, params);
	mlx_hook(params->window, 3, 0, res, params);
	mlx_loop_hook(params->mlx, update, params);
	mlx_hook(params->window, 17, 0, ft_close, params);
}

void	mini_main(t_params *params)
{
	get_resolution(params);
	get_no_texture(params);
	get_so_texture(params);
	get_we_texture(params);
	get_ea_texture(params);
	get_sprite(params);
	get_ciel_color(params);
	get_floor_color(params);
	get_map(params);
	ini_params(params);
	init_player(params);
	init_tex_sprite(params);
	open_win(params);
	set_sprite(params->path_sprite, params);
	ini_image(params);
	init_key(params);
	texture_position(params);
}

int		main(int ac, char **ag)
{
	t_params *params;

	if (!(params = (t_params *)malloc(sizeof(t_params))))
		returns("\n");
	params->info = malloc(sizeof(t_info));
	ft_bzero(params->info, sizeof(t_info));
	if (!(params->player = malloc(sizeof(t_player))))
		returns("\n");
	ft_bzero(params->player, sizeof(t_player));
	check_ac(ac);
	check_name_map(ag[1], params);
	mini_main(params);
	draw(params);
	mlx(params);
	if (ac > 2 && !ft_strncmp("-save", ag[2], ft_strlen(ag[2])))
	{
		create_bitmap(params->texx, "src/cub3d.bmp");
		returns("done");
	}
	else if (ac > 2 && ft_strncmp("-save", ag[2], ft_strlen(ag[2])))
		returns("error\n use -save for save image as bmp");
	else
		mlx_loop(params->mlx);
	return (0);
}
