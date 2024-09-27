# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgori <fgori@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 11:32:36 by fgori             #+#    #+#              #
#    Updated: 2024/02/02 13:46:49 by fgori            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

file = ./ft_atp/ft_atoi.c\
		./ft_atp/ft_itoa.c\
		./ft_atp/ft_memcpy.c\
		./ft_atp/ft_memmove.c\
		./ft_atp/ft_striteri.c\
		./ft_atp/ft_strnstr.c\
		./ft_atp/ft_tolower.c\
		./ft_atp/ft_toupper.c\
		./ft_controll/ft_bzero.c\
  		./ft_controll/ft_isalnum.c\
		./ft_controll/ft_isalpha.c\
		./ft_controll/ft_isascii.c\
		./ft_controll/ft_isdigit.c\
		./ft_controll/ft_strlen.c\
		./ft_controll/ft_strncmp.c\
		./ft_controll/ft_strrchr.c\
		./ft_controll/ft_isprint.c\
		./ft_controll/ft_memchr.c\
		./ft_controll/ft_memcmp.c\
		./ft_controll/ft_memset.c\
		./ft_controll/ft_strchr.c\
		./ft_controll/ft_strlcat.c\
		./ft_controll/ft_strlcpy.c\
		./ft_gnl/get_next_line_bonus.c\
		./ft_gnl/get_next_line_utils_bonus.c\
		./ft_fd/ft_putendl_fd.c\
		./ft_fd/ft_putnbr_fd.c\
		./ft_fd/ft_putchar_fd.c\
		./ft_fd/ft_putstr_fd.c\
  		./ft_malloc/ft_calloc.c\
		./ft_malloc/ft_split.c\
		./ft_printf/ft_putvod.c\
		./ft_printf/ft_putchr.c\
		./ft_printf/ft_printf.c\
		./ft_malloc/ft_strdup.c\
		./ft_malloc/ft_strjoin.c\
		./ft_malloc/ft_strmapi.c\
		./ft_malloc/ft_strtrim.c\
		./ft_malloc/ft_substr.c\

fbonus = ./ft_lst/ft_lstadd_front.c\
			./ft_lst/ft_lstadd_back.c\
			./ft_lst/ft_lstclear.c\
			./ft_lst/ft_lstdelone.c\
			./ft_lst/ft_lstiter.c\
			./ft_lst/ft_lstlast.c\
			./ft_lst/ft_lstmap.c\
			./ft_lst/ft_lstnew.c\
			./ft_lst/ft_lstsize.c
cc = cc

flag = -Wall -Wextra -Werror -I./lib/

NAME = libft.a

NAMEO = $(file:.c=.o)

objbonus = $(fbonus:.c=.o)

all: $(NAME)

$(NAME): $(NAMEO)
	ar -rc $(NAME) $(NAMEO)

bonus: $(NAME) $(objbonus)
	ar -rc $(NAME) $(objbonus)

%.o: %.c 
	$(cc) $(flag) -c $< -o $@

clean:
	rm -f $(NAMEO) $(objbonus)

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re bonus