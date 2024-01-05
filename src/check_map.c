/* 
	Check map module of the game So long author Roman Protchev v 2.0
	contains functions:
	-- static (local):
		check_shape - checks for size & shape
		check_edge - checks edges
		check_symbols - checks for valid symbols & only one start and one exit
		error_map_exit - if map error free map,print message, exit game
	-- global:
		check_map - complete checks map and setups bits for appropriate errors
*/
#include "so_long.h"

// checks for size & shape
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

// checks edges
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

// checks for valid symbols & only one start and one exit
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
		else if (map->map_chars[y][x] == EXIT_CLOSE)
			exits++;
		else if (!(map->map_chars[y][x] == WALL || \
				map->map_chars[y][x] == '0' || map->map_chars[y][x] == COLLECT))
			return (ERR_SYMBOLS);
	}
	if (starts != 1)
		return (ERR_START);
	if (exits != 1)
		return (ERR_EXIT);
	return (0);
}

// if map error free map & print message & exit with error code
static void	error_map_exit(int error_code, t_map *map)
{
	free_map(map);
	if ((error_code & ERR_SHAPE) == ERR_SHAPE)
		ft_putendl_fd("The map is not rectangle.", 1);
	if ((error_code & ERR_SIZE) == ERR_SIZE)
		ft_putendl_fd("The map is too small.", 1);
	if ((error_code & ERR_EDGE) == ERR_EDGE)
		ft_putendl_fd("The map isn't closed.", 1);
	if ((error_code & ERR_COLLECT) == ERR_COLLECT)
		ft_putendl_fd("The map must have at least one item to collect.", 1);
	if ((error_code & ERR_START) == ERR_START)
		ft_putendl_fd("The map must have one start position.", 1);
	if ((error_code & ERR_EXIT) == ERR_EXIT)
		ft_putendl_fd("The map must have one exit.", 1);
	if ((error_code & ERR_SYMBOLS) == ERR_SYMBOLS)
		ft_putendl_fd("The map has invalid symbols", 1);
	exit (error_code);
}

// complete checks map and setups bits for appropriate errors
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
		error_map_exit(valid_code, map);
}
