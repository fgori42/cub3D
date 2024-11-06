# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgori <fgori@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 14:34:18 by fgori             #+#    #+#              #
#    Updated: 2024/11/06 12:14:48 by fgori            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./src/
INCLUDE = ./include

LIB = ./include/libft/lib
LIBM = ./include/minilibx-linux

file = $(addprefix $(SRC), main.c parsing.c minimap.c lst_utils.c gun.c \
		print_world.c raycast2.c raycast.c lst_utils2.c parsing_textur.c\
		parsing_map.c parsing_map_utils.c init.c movement.c input.c get_color.c\
		game_managemet.c)

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(file)
		@make all -C $(INCLUDE)/libft
		@make all -C $(INCLUDE)/minilibx-linux
		cc $(CFLAGS) -I./include -I./include/libft/lib -I./include/minilibx-linux -L./include/libft -L./include/minilibx-linux $(file) $(MLX_FLAGS) -lft -o cub3D


clean:
		@echo "nothing to clean"

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re