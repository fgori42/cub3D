# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgori <fgori@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 14:34:18 by fgori             #+#    #+#              #
#    Updated: 2024/09/30 10:04:27 by fgori            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./src/
INCLUDE = ./include

LIB = ./include/libft/lib
LIBM = ./include/minilibx-linux

file = $(addprefix $(SRC), main.c)

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(file)
		@make all -C $(INCLUDE)/libft
		@make all -C $(INCLUDE)/minilibx-linux
		cc $(CFLAGS) -I./include -I./include/libft/lib -I./include/minilibx-linux -L./include/libft -L./include/minilibx-linux ./src/main.c $(MLX_FLAGS) -lft -o cub3D


clean:
		make clean -C $(INCLUDE)/libft

fclean: clean
		make fclean -C $(LFT)
		make clean -C $(DIR_MLX)
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re