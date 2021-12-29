/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 19:42:17 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/29 19:47:30 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	game->win = mlx_new_window(game->mlx, 1024, 768, "so_long");
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
	{
		mlx_destroy_window(game->mlx, game->win);
		game_exit(10, game);
	}
	printf ("Keycode - %d\n", key);
	if (key == KEY_DOWN || key == KEY_UP || key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (player_move(key, game->map))
		{
			print_steps(++game->steps);
			if (game_over(game->map))
				game_exit(0, game);
		}
		print_map(game->map);
	}
	return (0);
}

static int	close_win_hook(t_game *game)
{
	game_exit(11, game);
	return (0);
}

void	game_go(t_map *map)
{
	t_game	*game;

	game = game_init(map);
	print_map(game->map);
	mlx_hook(game->win, 17, 0, close_win_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop(game->mlx);
}
