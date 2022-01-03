/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 22:53:27 by nmordeka          #+#    #+#             */
/*   Updated: 2022/01/03 18:00:31 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	print_steps_bonus(t_game *game)
{
	char	*step_str;

	step_str = ft_itoa(game->steps);
	if (step_str)
	{
		mlx_string_put(game->mlx, game->win, IMG_SIZE - 16, (IMG_SIZE / 3), \
			0xffffffff, "STEPS :");
		mlx_string_put(game->mlx, game->win, IMG_SIZE * 2 - 16, \
			(IMG_SIZE / 3), 0xffffffff, step_str);
		free(step_str);
	}
}

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

static void	print_win(t_rect win, t_game *game)
{
	size_t	x;
	size_t	y;
	char	ch;
	void	*img;

	y = -1;
	while (++y < win.h)
	{
		x = -1;
		while (++x < win.w)
		{
			ch = game->map->map_chars[win.base.y + y][win.base.x + x];
			img = get_img_ptr(ch, game);
			mlx_put_image_to_window(game->mlx, game->win, img,
				x * IMG_SIZE, y * IMG_SIZE);
		}
	}
	print_steps_bonus(game);
}

static void	set_win_pos(size_t *pos, size_t *len, size_t p_pos, size_t w_wide)
{
	size_t	wide_max;

	wide_max = *len;
	*pos = p_pos - 1;
	while ((int)*pos >= 0 && p_pos - (*pos) <= w_wide / 2)
		(*pos)--;
	(*pos)++;
	*len = wide_max - *pos;
}

int	print_sprite_map(t_game	*game)
{
	t_rect	win;
	t_point	w_max;

	mlx_clear_window(game->mlx, game->win);
	win.w = game->map->width;
	w_max.x = WIN_W / IMG_SIZE;
	if (w_max.x > game->map->width)
		win.base.x = 0;
	else
		set_win_pos(&win.base.x, &win.w, game->map->player.x, w_max.x);
	win.h = game->map->height;
	w_max.y = WIN_H / IMG_SIZE;
	if (w_max.y > game->map->height)
		win.base.y = 0;
	else
		set_win_pos(&win.base.y, &win.h, game->map->player.y, w_max.y);
	print_win(win, game);
	return (0);
}
