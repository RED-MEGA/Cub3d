# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 16:20:52 by reben-ha          #+#    #+#              #
#    Updated: 2023/09/04 14:43:25 by reben-ha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc -g -Ofast

FLAGS = $(FW) -fsanitize=address #-Wall -Wextra -Werror

HEADERS = -I ./include  -I include/MLX42/include

LIBFT = lib/libft.a

LIBS = $(LIBFT) lib/libmlx42.a -dl -lglfw -L$(shell brew --prefix glfw)/lib -pthread -lm

INCLUDE = include/global.h include/cub3d.h include/tools.h include/libft.h

SRC = main.c \
		parsing/parsing.c \
		parsing/attributes.c \
		parsing/check.c \
		parsing/info.c \
		parsing/map_parse.c \
		parsing/map_check.c \
		parsing/player.c \
		minimap/handle_keys.c \
		minimap/map_draw.c \
		minimap/player_draw.c \
		raycasting/ray_cast.c \
		rendering/rays_calc.c \
		rendering/render.c \
		rendering/floor_ceiling.c \
		tools/math_tools.c \
		tools/get_color.c \
		tools/error.c \
		tools/matdup.c \
		tools/free.c \
		tools/index_list.c \
		tools/compare.c \
		tools/mlx_put_pixel_p.c \
		tools/cleanup_tools.c \
		textures/texture.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) #$(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

# $(LIBFT): include/libft.h
# 	make -C libft             lib/libft.a

%.o: %.c $(INCLUDE)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

clean :
	rm -rf $(OBJ)
# $(LIBFT)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
