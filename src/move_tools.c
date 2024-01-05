/* 
	Player move module of the game So long author Roman Protchev v 2.0
	contains functions:
	-- static (local):
		get_new_x - return destination x 
		get_new_y - return destination y
		valid_dest - return true if move possible
	-- global:
		player_move - changes map and return true if player moved
*/
#include "so_long.h"

static size_t	get_new_x(int key, t_map *map)
{
	size_t	new_x;

	new_x = map->player.x;
	if (key == KEY_LEFT)
		new_x--;
	else if (key == KEY_RIGHT)
		new_x++;
	return (new_x);
}

static size_t	get_new_y(int key, t_map *map)
{
	size_t	new_y;

	new_y = map->player.y;
	if (key == KEY_UP)
		new_y--;
	else if (key == KEY_DOWN)
		new_y++;
	return (new_y);
}

static int	valid_dest(size_t x, size_t y, t_map *map)
{
	char	ch;

	ch = map->map_chars[y][x];
	if (ch == COLLECT)
	{
		map->items_num--;
		return (FT_TRUE);
	}
	else if (ch == EMPTY || ch == EXIT_CLOSE)
		return (FT_TRUE);
	return (FT_FALSE);
}

int	player_move(int key, t_map *map)
{
	size_t	dest_x;
	size_t	dest_y;
	int		valid;

	dest_x = get_new_x(key, map);
	dest_y = get_new_y(key, map);
	valid = valid_dest(dest_x, dest_y, map);
	if (valid)
	{
		if (map->exit.x == map->player.x && map->exit.y == map->player.y)
			map->map_chars[map->player.y][map->player.x] = EXIT_CLOSE;
		else
			map->map_chars[map->player.y][map->player.x] = EMPTY;
		map->player.x = dest_x;
		map->player.y = dest_y;
		map->map_chars[map->player.y][map->player.x] = START_POS;
	}
	return (valid);
}
