/* 
	Main module of the game So long author Roman Protchev v 2.0
	contains functions:
	-- static (local):
		not_ber_ext	- detects string parameter ends with .ber
		game_over - returns true if level competed
		key_hook - called by part of minilibx's - mlx_key_hook if key pressed
		close_win_hook - called by minilibx's - mlx_hook if some event caused
	-- global:
		main - loads map, handles errors, runs global game circle in minilibx
*/
#include "so_long.h"

// checks for ber extention
static int	not_ber_ext(char *filename)
{
	char	*ext;
	int	result;

	if (!filename || ft_strlen(filename) < 5)
		return (FT_TRUE);
	ext = ft_substr(filename, ft_strlen(filename) - 4, 4);
	if (!ext)
		return (FT_TRUE);
	result = ft_strncmp(ext, ".ber", 4);
	free(ext);
	return (result);
}

// checks map for complete level
static int	game_over(t_map *map)
{
	if (map->items_num == 0 && (map->player.x == map->exit.x) && \
		(map->player.y == map->exit.y))
		return (FT_TRUE);
	return (FT_FALSE);
}

// if any keys pressed
static int	key_hook(int key, t_game *game)
{
	if (key == KEY_ESC)
		game_exit(0, "Esc exit", game);
	if (key == KEY_DOWN || key == KEY_UP || key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (player_move(key, game->map))
		{
			game->steps++;
			if (game_over(game->map))
				game_exit(0, "Level complete", game);
		}
	}
	return (0);
}

// if closed window of game
static int	close_win_hook(t_game *game)
{
	game_exit(0, "Close window", game);
	return (0);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_map			*map;
	t_game		*game;
	extern int	errno;

	game = NULL;
	if (argc != 2)
		game_exit (1, "Program needs one parameter with ber extention.", game);
	if (not_ber_ext(argv[1]))
		game_exit (1, "Mapfile hasn't .ber extention", game);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		game_exit(errno, NULL, game);
	map = read_map(fd);
	close(fd);
	if (!map)
		game_exit(1, "Empty line(s) in map", game);
	game = game_init(map);
	mlx_hook(game->win, 17, 0, close_win_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop_hook(game->mlx, print_sprite_map, game);
	mlx_loop(game->mlx);
	return (0);
}
