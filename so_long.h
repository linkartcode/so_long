/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 17:37:01 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/29 08:42:35 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libs/libft.h"
# include <mlx.h>
# include <string.h>
# include <stdio.h>

# define START_POS	'P'
# define EXIT_POS	'E'
# define COLLECT	'C'
# define WALL		'1'
# define EMPTY		'0'

# define ERR_SHAPE		1
# define ERR_SIZE		2
# define ERR_EDGE		4
# define ERR_COLLECT	8
# define ERR_START		16
# define ERR_EXIT		32
# define ERR_SYMBOLS	64

# define KEY_UP		13
# define KEY_DOWN	1
# define KEY_LEFT	0
# define KEY_RIGHT	2
# define KEY_ESC	53

typedef struct s_point
{
	size_t	x;
	size_t	y;
}	t_point;

typedef struct s_map
{
	t_point	player;
	t_point	exit;
	size_t	width;
	size_t	height;
	int		items_num;
	char	**map_chars;
}	t_map;

typedef struct s_game
{
	t_map	*map;
	size_t  steps;
	void	*mlx;
	void	*win;
}	t_game;

t_map	*read_map(int fd);
void	check_map(t_map *map);
void	free_map(t_map *map);
void	error_exit(char	*err_message);

#endif