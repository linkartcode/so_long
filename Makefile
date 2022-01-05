# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 22:47:06 by nmordeka          #+#    #+#              #
#    Updated: 2022/01/05 19:38:37 by nmordeka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long
NAME_B		= so_long_bonus
#
LIBFT 		= libft.a
LIBS_PATH	= ./lib
#
SRCS		= 	main.c		check_map.c		pars_map.c		sprite_tools.c \
				exit_tools.c	move_tools.c 	print_tools.c 
SRCS_B		=	main_bonus.c			check_map_bonus.c		pars_map_bonus.c \
				sprite_tools_bonus.c	exit_tools_bonus.c 		move_tools_bonus.c \
				print_tools_bonus.c 
#
HEADER		=	so_long.h
HEADER_B	=	so_long_bonus.h
OBJ			=	$(patsubst %.c, %.o, $(SRCS))
OBJ_B		=	$(patsubst %.c, %.o, $(SRCS_B))
#
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I.
RM 			=	rm -f
LMX 		= 	-lmlx -framework OpenGL -framework Appkit
#
.PHONY	:	all clean fclean re bonus force
#
all	: $(NAME)
#
$(NAME)	: $(LIBS_PATH)/$(LIBFT) $(OBJ)
	$(CC) -L$(LIBS_PATH) -lft $(LMX) -o $@ $(OBJ)
#
$(LIBS_PATH)/$(LIBFT) : force
	$(MAKE) -C $(LIBS_PATH)/
#
force : ;
#
$(filter %.o,$(OBJ)): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
#
bonus : $(NAME_B)
#
$(NAME_B) : $(LIBS_PATH)/$(LIBFT) $(OBJ_B)
	$(CC) -L$(LIBS_PATH) -lft $(LMX) -o $@ $(OBJ_B)
#
$(filter %.o,$(OBJ_B)): %.o: %.c $(HEADER_B)
	$(CC) $(CFLAGS) -c $< -o $@
#
clean :
	$(MAKE) -C $(LIBS_PATH)/ clean
	$(RM) $(OBJ) $(OBJ_B)
#
fclean	:	clean
	$(MAKE) -C $(LIBS_PATH)/ fclean
	$(RM) $(NAME) $(NAME_B)
#
re	:	fclean all
#