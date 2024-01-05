/* 
	.h module of the game So long author Roman Protchev v 2.0
	contains all definitions of game
*/
#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libs/libft/libft.h"
# include "./libs/minilibx/mlx.h"
# include <string.h>

// codes in filemap  
# define START_POS	'P'
# define EXIT_CLOSE	'E'
# define EXIT_OPEN	'O'
# define COLLECT		'C'
# define WALL			'1'
# define EMPTY			'0'

// volumes of errcodes
# define ERR_SHAPE	1
# define ERR_SIZE		2
# define ERR_EDGE		4
# define ERR_COLLECT	8
# define ERR_START	16
# define ERR_EXIT		32
# define ERR_SYMBOLS	64

// keyboard scan codes
# define KEY_UP		13
# define KEY_DOWN		1
# define KEY_LEFT		0
# define KEY_RIGHT	2
# define KEY_ESC		53
// size of sprites
# define IMG_SIZE		64
// max size of the game window 
# define WIN_W			1024
# define WIN_H			768

// point type
typedef struct s_point
{
	size_t	x;
	size_t	y;
}	t_point;

// rectangle type
typedef struct s_rect
{
	size_t	x;
	size_t	y;
	size_t	w;
	size_t	h;
}	t_rect;

// map of the game - all sizes in row and col units
typedef struct s_map
{
	t_point	player;
	t_point	exit;
	size_t	width;
	size_t	height;
	int		items_num;
	char		**map_chars;
}	t_map;

// sprite obj - map_index - char code in map
// w & h - size in pixels
typedef struct s_sprite
{
	char	map_index;
	int	w;
	int	h;
	void	*img_data;
}	t_sprite;

// collection of game sprites
typedef struct s_items
{
	t_sprite	*empty;
	t_sprite	*wall;
	t_sprite	*player;
	t_sprite	*exit;
	t_sprite	*exit_open;
	t_sprite	*collect;
}	t_items;

// all data for game
// 	*mlx & *win - needs for minilibx
// 	steps - counter for player's steps
//		width_win & height_win - size of window in map units
typedef struct s_game
{
	void		*mlx;
	void		*win;
	size_t	steps;
	size_t	width_win;
	size_t	height_win;
	t_items	*sprites;
	t_map		*map;
}	t_game;

t_map		*read_map(int fd);
t_items	*read_sprites(t_game *game);

void		check_map(t_map *map);
void		free_map(t_map *map);
void		free_items(t_items *items, void *mlx);

int		player_move(int key, t_map *map);
int		print_sprite_map(t_game	*game);

t_game	*game_init(t_map *map);
int		game_exit(int exit_code, char *err_message, t_game *game);

#endif
