/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 19:38:15 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/29 19:38:21 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_sprite(t_sprite *sprite, void *mlx)
{
	if (!sprite)
		return ;
	if (sprite->img_data)
		mlx_destroy_image(mlx, sprite->img_data);
	free(sprite);
}

void	free_items(t_items *items, void *mlx)
{
	if (!items)
		return ;
	if (items->empty)
		free_sprite(items->empty, mlx);
	if (items->wall)
		free_sprite(items->wall, mlx);
	if (items->collect)
		free_sprite(items->collect, mlx);
	if (items->player)
		free_sprite(items->player, mlx);
	if (items->exit)
		free_sprite(items->exit, mlx);
	free (items);
}

static t_sprite	*sprite_init(char type, char *path, t_game *game)
{
	t_sprite	*spr;

	spr = malloc(sizeof(t_sprite));
	if (!spr)
		return (NULL);
	spr->map_index = type;
	spr->img_data = mlx_xpm_file_to_image(game->mlx, path, &spr->w, &spr->h);
	return (spr);
}

t_items	*read_sprites(t_game *game)
{
	t_items	*items;

	items = malloc(sizeof(t_items));
	if (!items)
		return (NULL);
	items->empty = sprite_init(EMPTY, "image_xpm/empty_64.xpm", game);
	items->wall = sprite_init(WALL, "image_xpm/wall_64.xpm", game);
	items->player = sprite_init(START_POS, "image_xpm/dolphin_64.xpm", game);
	items->exit = sprite_init(EXIT_POS, "image_xpm/exit_64.xpm", game);
	items->collect = sprite_init(COLLECT, "image_xpm/collect_64.xpm", game);
	if (!items->collect || !items->wall || !items->exit \
		|| !items->empty || !items->player)
		free_items(items, game->mlx);
	return (items);
}
