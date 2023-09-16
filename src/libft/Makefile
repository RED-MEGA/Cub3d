# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 12:26:41 by azarda            #+#    #+#              #
#    Updated: 2023/09/16 18:44:43 by reben-ha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../../lib/libft.a

INCLUDE =  ../../include/libft.h

HEADERS = -I ../../include -I ../../include/MLX42/include

SRC = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_printf.c \
		ft_putchar_fd.c \
		ft_putchar_printf.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putnbr_hex_printf.c \
		ft_putnbr_pos_printf.c \
		ft_putnbr_printf.c \
		ft_putptr_printf.c \
		ft_putstr_fd.c \
		ft_putstr_printf.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		get_next_line.c \
		get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)

%.o : %.c $(INCLUDE)
	cc -Wall -Wextra -Werror $(HEADERS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re