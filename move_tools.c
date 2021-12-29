/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:26:55 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/29 13:30:18 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_point	*get_dest_point(int key, t_map *map)
{
	t_point	*dest;

	dest = malloc(sizeof(t_point));
	if (!dest)
		return (NULL);
	dest->x = map->player.x;
	dest->y = map->player.y;
	if (key == KEY_UP)
		dest->y--;
	else if (key == KEY_DOWN)
		dest->y++;
	else if (key == KEY_LEFT)
		dest->x--;
	else
		dest->x++;
	return (dest);
}

static int	valid_dest(t_point *dest, t_map *map)
{
	char	ch;

	ch = map->map_chars[dest->y][dest->x];
	if (ch == COLLECT)
	{
		map->items_num--;
		return (FT_TRUE);
	}
	else if (ch == EMPTY || ch == EXIT_POS)
		return (FT_TRUE);
	return (FT_FALSE);
}

int	player_move(int key, t_map *map)
{
	t_point	*dest;
	int		valid;

	dest = get_dest_point(key, map);
	valid = valid_dest(dest, map);
	if (valid)
	{
		if (map->exit.x == map->player.x && map->exit.y == map->player.y)
			map->map_chars[map->player.y][map->player.x] = EXIT_POS;
		else
			map->map_chars[map->player.y][map->player.x] = EMPTY;
		map->player.x = dest->x;
		map->player.y = dest->y;
		map->map_chars[map->player.y][map->player.x] = START_POS;
	}
	if (dest)
		free (dest);
	return (valid);
}
