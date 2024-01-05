/* 
	Print map module of the game So long author Roman Protchev v 2.0
	contains functions:
	-- static (local):
		print_steps_bonus - prints value of steps
		get_img_ptr - returns image ptr sprite according the ch
		print_win - prints rectangle part of map
		get_base_pos - returns base coordinate for printing rectangle
	-- global:
		print_sprite_map - prints map
*/
#include "so_long.h"

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
	else if (ch == EXIT_CLOSE)
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

	y = 0;
	while (y < win.h)
	{
		x = 0;
		while (x < win.w)
		{
			ch = game->map->map_chars[win.y + y][win.x + x];
			img = get_img_ptr(ch, game);
			mlx_put_image_to_window(game->mlx, game->win, img,
				x * IMG_SIZE, y * IMG_SIZE);
			x++;
		}
		y++;
	}
	print_steps_bonus(game);
}

static int	get_base_pos(size_t max, size_t wide, size_t pos)
{
	int	base;

	base = pos - wide / 2;
	if (base < 0)
		base = 0;
	else if (base > (int)(max - wide))
		base = max - wide;
	return (base);
}

int	print_sprite_map(t_game	*game)
{
	t_rect	win;

	mlx_clear_window(game->mlx, game->win);
	win.w = game->width_win;
	if (win.w > game->map->width)
		win.x = 0;
	else
		win.x = get_base_pos(game->map->width, win.w, game->map->player.x);
	win.h = game->height_win;
	if (win.h > game->map->height)
		win.y = 0;
	else
		win.y = get_base_pos(game->map->height, win.h, game->map->player.y);
	print_win(win, game);
	return (0);
}
