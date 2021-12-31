/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 19:35:00 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/31 17:23:44 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	error_exit(char	*err_message)
{
	extern int	errno;

	ft_putendl_fd("Error", 1);
	if (err_message)
		ft_putendl_fd(err_message, 1);
	else
		ft_putendl_fd(strerror(errno), 1);
	exit (0);
}

int	game_exit(int exit_code, t_game *game)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->sprites)
			free_items(game->sprites, game->mlx);
		free(game);
	}
	exit (exit_code);
}
