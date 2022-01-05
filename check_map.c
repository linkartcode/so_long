/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 23:03:49 by nmordeka          #+#    #+#             */
/*   Updated: 2022/01/04 11:36:27 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_shape(t_map *map)
{
	size_t	height;

	height = 0;
	while (height < map->height)
	{
		if (ft_strlen(map->map_chars[height]) != map->width)
			break ;
		height++;
	}
	if (map->height != height)
		return (ERR_SHAPE);
	if ((map->width + map->height) < 8 && (map->width < 4 || map->height < 4))
		return (ERR_SIZE);
	return (0);
}

static int	check_edge(t_map *map)
{
	size_t	i;
	int		valid;

	valid = FT_TRUE;
	i = -1;
	while (++i < map->width)
		if (map->map_chars[0][i] != WALL)
			valid = FT_FALSE;
	i = 0;
	while (++i < map->height - 1)
		if ((map->map_chars[i][0] != WALL) || \
			(map->map_chars[i][map->width - 1] != WALL))
			valid = FT_FALSE;
	i = -1;
	while (++i < map->width)
		if (map->map_chars[map->height - 1][i] != WALL)
			valid = FT_FALSE;
	if (!valid)
		return (ERR_EDGE);
	else
		return (0);
}

static int	check_symbols(t_map *map)
{
	size_t	y;
	size_t	x;
	int		starts;
	int		exits;

	starts = 0;
	exits = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
			if (map->map_chars[y][x] == START_POS)
				starts++;
		else if (map->map_chars[y][x] == EXIT_POS)
			exits++;
		else if (!(map->map_chars[y][x] == '1' || map->map_chars[y][x] == '0' \
			|| map->map_chars[y][x] == COLLECT))
			return (ERR_SYMBOLS);
	}
	if (starts != 1)
		return (ERR_START);
	if (exits != 1)
		return (ERR_EXIT);
	return (0);
}

void	check_map(t_map *map)
{
	int	valid_code;

	valid_code = 0;
	valid_code |= check_shape(map);
	valid_code |= check_edge(map);
	if (map->items_num < 1)
		valid_code |= ERR_COLLECT;
	valid_code |= check_symbols(map);
	if (valid_code != 0)
	{
		free_map(map);
		if ((valid_code & ERR_SHAPE) == ERR_SHAPE)
			error_exit("The map is not rectangle.");
		if ((valid_code & ERR_SIZE) == ERR_SIZE)
			error_exit("The map is too small.");
		if ((valid_code & ERR_EDGE) == ERR_EDGE)
			error_exit("The map isn't closed.");
		if ((valid_code & ERR_COLLECT) == ERR_COLLECT)
			error_exit("Map must have at least one item to collect.");
		if ((valid_code & ERR_START) == ERR_START)
			error_exit("Map must have one start position.");
		if ((valid_code & ERR_EXIT) == ERR_EXIT)
			error_exit("Map must have one exit.");
		error_exit("Map has invalid symbols");
	}
}
