# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 16:20:52 by reben-ha          #+#    #+#              #
#    Updated: 2023/07/25 23:48:19 by reben-ha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# CC = cc
CC = gcc -g

FLAGS = -Wall -Wextra -Werror

INCLUDE = global.h cub3d.h utils.h libft.h

SRC = main.c \
		libft/ft_atoi.c \
		libft/ft_bzero.c \
		libft/ft_calloc.c \
		libft/ft_isalnum.c \
		libft/ft_isalpha.c \
		libft/ft_isascii.c \
		libft/ft_isdigit.c \
		libft/ft_isprint.c \
		libft/ft_itoa.c \
		libft/ft_lstadd_back.c \
		libft/ft_lstadd_front.c \
		libft/ft_lstclear.c \
		libft/ft_lstdelone.c \
		libft/ft_lstiter.c \
		libft/ft_lstlast.c \
		libft/ft_lstnew.c \
		libft/ft_lstsize.c \
		libft/ft_memchr.c \
		libft/ft_memcmp.c \
		libft/ft_memcpy.c \
		libft/ft_memmove.c \
		libft/ft_memset.c \
		libft/ft_printf.c \
		libft/ft_putchar_fd.c \
		libft/ft_putchar_printf.c \
		libft/ft_putendl_fd.c \
		libft/ft_putnbr_fd.c \
		libft/ft_putnbr_hex_printf.c \
		libft/ft_putnbr_pos_printf.c \
		libft/ft_putnbr_printf.c \
		libft/ft_putptr_printf.c \
		libft/ft_putstr_fd.c \
		libft/ft_putstr_printf.c \
		libft/ft_split.c \
		libft/ft_strchr.c \
		libft/ft_strdup.c \
		libft/ft_striteri.c \
		libft/ft_strjoin.c \
		libft/ft_strlcat.c \
		libft/ft_strlcpy.c \
		libft/ft_strlen.c \
		libft/ft_strmapi.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \
		libft/ft_strrchr.c \
		libft/ft_substr.c \
		libft/get_next_line.c \
		libft/get_next_line_utils.c \
		utils/error.c \
		utils/matdup.c \
		utils/free.c \
		utils/index_list.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re