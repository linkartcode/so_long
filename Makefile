# Makefile for building the game So Long
NAME		= so_long

# libs code
LIBS_PATH 	= ./libs

LIBFT_NAME 	= libft.a
LIBFT_PATH	= libft

MINILIBX_NAME	= libmlx.a
MINILIBX_PATH 	= minilibx

# source code
SRCS_PATH	=	./src
SRCS			= 	$(SRCS_PATH)/so_long.c		$(SRCS_PATH)/check_map.c		$(SRCS_PATH)/pars_map.c\
					$(SRCS_PATH)/sprite_tools.c	$(SRCS_PATH)/exit_tools.c	$(SRCS_PATH)/move_tools.c\
					$(SRCS_PATH)/print_tools.c
OBJ			=	$(patsubst %.c, %.o, $(SRCS))
HEADER		=	$(SRCS_PATH)/so_long.h

# compiler and command options
CC				=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I.
RM 			=	rm -f
LMX 			= 	-lmlx -framework OpenGL -framework Appkit

#
.PHONY	:	all clean fclean re force

all	: $(NAME)
# builds main file from obj 
$(NAME)	: $(LIBS_PATH)/$(LIBFT_PATH)/$(LIBFT_NAME) $(LIBS_PATH)/$(MINILIBX_PATH)/$(MINILIBX_NAME) $(OBJ)
	$(CC) -L$(LIBS_PATH)/$(LIBFT_PATH) -lft -L$(LIBS_PATH)/$(MINILIBX_PATH) $(LMX) -o $@ $(OBJ)

# builds libft lib
$(LIBS_PATH)/$(LIBFT_PATH)/$(LIBFT_NAME) : force
	$(MAKE) -C $(LIBS_PATH)/$(LIBFT_PATH)/

# builds minilibx lib
$(LIBS_PATH)/$(MINILIBX_PATH)/$(MINILIBX_NAME) : force
	$(MAKE) -C $(LIBS_PATH)/$(MINILIBX_PATH)/

# force return
force : ;

# builds obj files from c files
$(filter %.o,$(OBJ)): %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# removes all obj files (lib and source)
clean :
	$(MAKE) -C $(LIBS_PATH)/$(LIBFT_PATH)/ clean
	$(MAKE) -C $(LIBS_PATH)/$(MINILIBX_PATH)/ clean
	$(RM) $(OBJ)
# removes all files made through compile 
fclean	:	clean
	$(MAKE) -C $(LIBS_PATH)/$(LIBFT_PATH)/ fclean
	$(MAKE) -C $(LIBS_PATH)/$(MINILIBX_PATH)/ clean
	$(RM) $(NAME)
# force rebuilds exec file 
re	:	fclean all
#