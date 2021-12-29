/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:47:32 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/29 12:11:16 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(char	*err_message)
{
	extern int	errno;

	ft_putendl_fd("Error", 1);
	if (err_message)
		ft_putendl_fd(err_message, 1);
	else
		ft_putendl_fd(strerror(errno), 1);
	//sleep(10000);
	exit (0);
}

static int	not_ber_ext(char *filename)
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

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	printf("Map width - %zu, height - %zu\n", map->width, map->height);
	printf("Items to collect = %d\n", map->items_num);
	while (map->map_chars[i])
	{
		ft_putendl_fd(map->map_chars[i], 1);
		i++;
	}
}

int	game_over(t_map *map)
{
	if (map->items_num == 0 && (map->player.x == map->exit.x) && 
		(map->player.y == map->exit.y))
		return (FT_TRUE);
	return (FT_FALSE);
}

int	game_exit(int exit_code, t_game *game)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		free(game);
	}
	printf("Game Over! Exit code %d\n", exit_code);
	//sleep(15);
	exit (0);
}

t_game	*game_init(t_map *map)
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
	return (game);
}

t_point	*get_dest_point(int key, t_map *map)
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

int	valid_dest(t_point *dest, t_map *map)
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

int	player_move(int	key, t_map *map)
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

void	print_steps(int steps)
{
	printf("steps made - %d\n", steps);
}

int	key_hook (int key, t_game *game)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		game_exit(2, game);
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

int	close_win_hook(t_game *game)
{
	game_exit(3, game);
	return (0);
}

void	game(t_map *map)
{
	t_game	*game;

	game = game_init(map);
	mlx_hook(game->win, 17, 0, close_win_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	*map;

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
		error_exit("Problem with end of map or with memory allocation.");
	game(map);
}
