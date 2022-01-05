/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 22:46:43 by nmordeka          #+#    #+#             */
/*   Updated: 2022/01/05 19:37:36 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	game_over(t_map *map)
{
	if (map->items_num == 0 && (map->player.x == map->exit.x) && \
		(map->player.y == map->exit.y))
		return (FT_TRUE);
	return (FT_FALSE);
}

static t_game	*game_init(t_map *map)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		free_map(map);
		error_exit("No enought mamory for game!");
	}
	game->map = map;
	game->steps = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit(1, game);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "so_long");
	if (!game->win)
		game_exit(2, game);
	game->sprites = read_sprites(game);
	if (!game->sprites)
		game_exit(3, game);
	return (game);
}

static int	key_hook(int key, t_game *game)
{
	if (key == KEY_ESC)
		game_exit(10, game);
	if (key == KEY_DOWN || key == KEY_UP || key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (player_move(key, game->map))
		{
			game->steps++;
			if (game_over(game->map))
				game_exit(0, game);
		}
	}
	return (0);
}

static int	close_win_hook(t_game *game)
{
	game_exit(11, game);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;
	t_game	*game;

	if (argc != 2)
		error_exit ("Program accept only one *.ber parameter");
	if (not_ber_ext(argv[1]))
		error_exit ("Mapfile hasn't .ber extention");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit(NULL);
	map = read_map(fd);
	close(fd);
	if (!map)
		error_exit("Empty line(s) in map");
	game = game_init(map);
	mlx_hook(game->win, 17, 0, close_win_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop_hook(game->mlx, print_sprite_map, game);
	mlx_loop(game->mlx);
	return (0);
}
