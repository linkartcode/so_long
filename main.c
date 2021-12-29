/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:47:32 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/29 19:46:30 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	print_steps(int steps)
{
	printf("steps made - %d\n", steps);
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
	game_go(map);
}
