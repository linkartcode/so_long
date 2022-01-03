/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 22:46:43 by nmordeka          #+#    #+#             */
/*   Updated: 2022/01/02 20:19:42 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
		error_exit("Empty line(s) in map");
	game_go(map);
}
