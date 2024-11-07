# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgori <fgori@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 14:34:18 by fgori             #+#    #+#              #
#    Updated: 2024/11/07 11:33:12 by fgori            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/
INCLUDE = ./include

LIB = $(INCLUDE)/libft/lib
LIBM = $(INCLUDE)/minilibx-linux

file = $(addprefix $(SRC), main.c parsing.c minimap.c lst_utils.c gun.c \
		print_world.c raycast2.c raycast.c lst_utils2.c parsing_textur.c\
		parsing_map.c parsing_map_utils.c init.c movement.c input.c get_color.c\
		game_managemet.c)

NAME = cub3D

fileO = $(file:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE) -I$(LIB) -I$(LIBM)
MLX_FLAGS = -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(fileO)
		@make all -C $(INCLUDE)/libft
		@make all -C $(INCLUDE)/minilibx-linux
		$(CC) $(CFLAGS) $(fileO) -L$(INCLUDE)/libft -L$(INCLUDE)/minilibx-linux $(MLX_FLAGS) -lft -o $(NAME)

%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@

clean:
		rm -f $(fileO)

fclean: clean
		make fclean -C $(INCLUDE)/libft
		make clean -C $(INCLUDE)/minilibx-linux
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re