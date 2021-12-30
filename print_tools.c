/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 06:43:29 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/30 06:54:18 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*get_img_ptr(char ch, t_game *game)
{
	void	*img;

	if (ch == EMPTY)
		img = game->sprites->empty->img_data;
	else if (ch == WALL)
		img = game->sprites->wall->img_data;
	else if (ch == COLLECT)
		img = game->sprites->collect->img_data;
	else if (ch == EXIT_POS)
		img = game->sprites->exit->img_data;
	else
		img = game->sprites->player->img_data;
	return (img);
}

int	print_sprite_map(t_game	*game)
{
	size_t	x;
	size_t	y;
	char	ch;
	void	*img;

	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
		{
			ch = game->map->map_chars[y][x];
			img = get_img_ptr(ch, game);
			mlx_put_image_to_window(game->mlx, game->win, img,
				x * IMG_SIZE, y * IMG_SIZE);
		}
	}
	return (0);
}

void	print_steps(int steps)
{
	printf("steps made - %d\n", steps);
}
