/* 
	Exit module of the game So long author Roman Protchev v 2.0
	contains functions:
	-- global:
		free_map - free memory of map
		game_exit - print error message, free memory of game, exit game with exit code
*/
#include "so_long.h"

// free memory of map
void	free_map(t_map *map)
{
	size_t	i;

	i = 0;
	if (map)
	{
		if (map->map_chars)
		{
			while (map->map_chars[i])
			{
				free(map->map_chars[i]);
				i++;
			}
			free(map->map_chars);
		}
		free(map);
	}
}

// print error message, free memory of game, exit game with exit code
int	game_exit(int exit_code, char *err_message, t_game *game)
{
	if (exit_code != 0)
		ft_putstr_fd("Error : ", 1);
	if (err_message)
		ft_putendl_fd(err_message, 1);
	else
		ft_putendl_fd(strerror(exit_code), 1);
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->sprites)
			free_items(game->sprites, game->mlx);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		free(game);
	}
	exit (exit_code);
}
