/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 06:43:29 by nmordeka          #+#    #+#             */
/*   Updated: 2022/01/05 19:15:57 by nmordeka         ###   ########.fr       */
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
	return ;
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

void	print_steps(int steps)
{
	ft_putstr_fd("steps - ", 1);
	ft_putnbr_fd(steps, 1);
	ft_putchar_fd('\n', 1);
}
