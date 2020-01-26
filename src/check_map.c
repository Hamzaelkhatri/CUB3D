/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helkhatr <helkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:17:11 by helkhatr          #+#    #+#             */
/*   Updated: 2020/01/26 02:20:28 by helkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

size_t		ft_strlen_w(const char *str)
{
	size_t	i;
	int		len;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == '2' ||
				str[i] == 'N' || str[i] == 'S' || str[i] == 'W' ||
				str[i] == 'E')
			len++;
		i++;
	}
	return (len);
}

int			ft_height(t_params *parms)
{
	char	*line;
	int		fd;

	fd = open("map.cub", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		parms->info->mapheight++;
		parms->info->mapwidth = ft_width_map(line);
	}
	return (0);
}

void		check_ac(int ac)
{
	if (ac < 2)
		returns("Error\n First argmet for map file, Second for save");
}

void		check_name_map(char *path, t_params *params)
{
	int i;

	i = ft_strlen(path);
	if (ft_strncmp(".cub", &path[i - 4], 3) != 0)
	{
		returns("Error\n PLEASE CHECK EXTENTION OF MAP FILE");
		exit(0);
	}
	else
	{
		params->fd = open(path, O_RDONLY);
		if (params->fd < 0)
			returns("CHECK your path");
		params->path = ft_strdup(path);
	}
}

void		check_map(char *str, t_params *params)
{
	int			i;
	size_t		len;

	i = 0;
	len = ft_strlen_w(str);
	if (len != params->info->mapwidth)
		returns("Error\nCHECK THE MAP");
	len = ft_strlen(str);
	if (str[0] != '1' || str[len - 1] != '1')
		returns("Error\nCHECK THE MAP");
	while (str[i] != '\0')
	{
		if (str[i] != '0' && str[i] != '1' &&
				str[i] != '2' && str[i] != 'N' &&
				str[i] != ' ' && str[i] != 'S' &&
				str[i] != 'E' && str[i] != 'W')
			returns("Error\nCHECK THE MAP");
		i++;
	}
}
