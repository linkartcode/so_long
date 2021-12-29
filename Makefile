# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 22:47:06 by nmordeka          #+#    #+#              #
#    Updated: 2021/12/29 19:42:50 by nmordeka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long
LIBFT 		= libft.a
#
LIBS_PATH	= ./libs
#
SRCS		= 	main.c		check_map.c		pars_map.c		sprite_tools.c \
				game.c		exit_tools.c	move_tools.c \
				
#
HEADER		=	so_long.h
OBJ			=	$(patsubst %.c, %.o, $(SRCS))
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
%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
#
bonus : all
#
clean :
	$(MAKE) -C $(LIBS_PATH)/ clean
	$(RM) $(OBJ)
#
fclean	:	clean
	$(MAKE) -C $(LIBS_PATH)/ fclean
	$(RM) $(NAME)
#
re	:	fclean all
#