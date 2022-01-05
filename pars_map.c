/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:15:00 by nmordeka          #+#    #+#             */
/*   Updated: 2022/01/05 19:06:05 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	not_ber_ext(char *filename)
{
	char	*ext;
	int		result;

	if (!filename || ft_strlen(filename) < 5)
		return (FT_TRUE);
	ext = ft_substr(filename, ft_strlen(filename) - 4, 4);
	if (!ext)
		return (FT_TRUE);
	result = ft_strncmp(ext, ".ber", 4);
	free(ext);
	return (result);
}

static char	**get_mapchars(int fd)
{
	char	*map_chars;
	char	*read_str;
	char	*tmp_str;
	char	**result;

	read_str = get_next_line(fd);
	if (!read_str)
		return (NULL);
	result = NULL;
	map_chars = ft_strdup("");
	while (read_str && read_str[0] != '\n')
	{
		tmp_str = ft_strjoin(map_chars, read_str);
		free(read_str);
		free(map_chars);
		map_chars = tmp_str;
		read_str = get_next_line(fd);
	}
	if (!read_str)
		result = ft_split(map_chars, '\n');
	else
		free(read_str);
	free(map_chars);
	return (result);
}

static void	read_fields(t_map *map)
{
	size_t	x;

	map->width = ft_strlen(map->map_chars[0]);
	map->height = -1;
	map->items_num = 0;
	while (map->map_chars[++map->height])
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->map_chars[map->height][x] == COLLECT)
				map->items_num++;
			else if (map->map_chars[map->height][x] == START_POS)
			{
				map->player.x = x;
				map->player.y = map->height;
			}
			else if (map->map_chars[map->height][x] == EXIT_POS)
			{
				map->exit.x = x;
				map->exit.y = map->height;
			}
		}
	}
}

t_map	*read_map(int fd)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map_chars = get_mapchars(fd);
	if (!(map->map_chars))
	{
		free(map);
		return (NULL);
	}
	read_fields(map);
	check_map(map);
	return (map);
}
