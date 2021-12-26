/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:47:32 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/26 09:09:37 by nmordeka         ###   ########.fr       */
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
	//printf("Start pos at x = %zu, y = %zu\n", map->player.x, map->player.y);
	//printf("Finish pos at x = %zu, y = %zu\n", map->exit.x, map->exit.y);
	printf("Items to collect = %d\n", map->items_num);
	while (map->map_chars[i])
	{
		ft_putendl_fd(map->map_chars[i], 1);
		i++;
	}
}

/* int	end_game(t_map map)
{
	if (map->items_num == 0 && (map->player->x == map->exit->x) && (map->player->y == map->exit->y))
		return (1);
	return (0);
}

void	game(t_map map)
{
	player_move(map, read_key());
	print_map(map);
}

void	game_over(int exit_code)
{
	printf("Game Over! Exit Code : %d \n", exit_code);
}
 */

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
	print_map(map);
	/* while (!end_game(map))
		game(map);
	game_over(end_game(map)); */
	free_map(map);
	//sleep(10000);
}
