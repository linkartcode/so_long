/* 
	 module of the game So long author Roman Protchev v 2.0
	contains functions:
	-- static (local):
		get_mapchars - reads map from file
		read_fields - analises map and fills all fields of map
		init_win_mlx - inits game window and handlеs errors
	-- global:
		read_map - read map from opened file descriptor fd
		game_init - init game and handles errors
*/
#include "so_long.h"

// reads map from file
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

// analises map and fills all fields of map
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
			else if (map->map_chars[map->height][x] == EXIT_CLOSE)
			{
				map->exit.x = x;
				map->exit.y = map->height;
			}
		}
	}
}

// read map from opened file descriptor fd
// return map or NULL if error
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

// inits game window and handlеs errors
static void	init_win_mlx(t_game *game)
{
	size_t	max_width;
	size_t	max_height;

	max_width = WIN_W / IMG_SIZE;
	max_height = WIN_H / IMG_SIZE;
	if (game->map->width > max_width)
		game->width_win = max_width;
	else
		game->width_win = game->map->width;
	if (game->map->height > max_height)
		game->height_win = max_height;
	else
		game->height_win = game->map->height;
	max_width = game->width_win * IMG_SIZE;
	max_height = game->height_win * IMG_SIZE;
	game->win = mlx_new_window(game->mlx, max_width, max_height, "so_long");
	if (!game->win)
		game_exit(2, "mlx window init error", game);
}

// init game and handles errors
t_game	*game_init(t_map *map)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		free_map(map);
		game_exit(1, "No enought mamory for game!", game);
	}
	game->map = map;
	game->steps = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit(1, "mlx init error", game);
	init_win_mlx(game);
	game->sprites = read_sprites(game);
	if (!game->sprites)
		game_exit(3, "sprites init error", game);
	return (game);
}
