# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 16:20:52 by reben-ha          #+#    #+#              #
#    Updated: 2023/09/14 15:37:39 by reben-ha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc -g -Ofast

FLAGS = #-fsanitize=address #-Wall -Wextra -Werror

HEADERS = -I ./include  -I include/MLX42/include

LIBFT = lib/libft.a

LIBS = $(LIBFT) lib/libmlx42.a -dl -lglfw -L$(shell brew --prefix glfw)/lib -pthread -lm

LIBSLINU = liblinux/libft.a liblinux/libmlx42.a -dl -lglfw -L$(shell  --prefix glfw)/lib -pthread -lm

INCLUDE = include/global.h include/cub3d.h include/tools.h include/libft.h

SRC = src/main.c \
	src/parsing/parsing.c \
	src/parsing/attributes.c \
	src/parsing/check.c \
	src/parsing/info.c \
	src/parsing/global.c \
	src/parsing/map_parse.c \
	src/parsing/map_check.c \
	src/parsing/player.c \
	src/minimap/map_draw.c \
	src/minimap/player_draw.c \
	src/raycasting/ray_cast.c \
	src/raycasting/ray_cast_utils.c \
	src/rendering/rays_calc.c \
	src/rendering/render.c \
	src/rendering/change_pos.c \
	src/rendering/floor_ceiling.c \
	src/rendering/sprite.c \
	src/tools/math_tools.c \
	src/tools/get_color.c \
	src/tools/error.c \
	src/tools/matdup.c \
	src/tools/free.c \
	src/tools/index_list.c \
	src/tools/compare.c \
	src/tools/mlx_put_pixel_p.c \
	src/tools/cleanup_tools.c \
	src/textures/texture.c \
	src/hooks/callback_utils.c \
	src/hooks/keyboard_callback.c \
	src/hooks/mouse_callback.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

linux : $(OBJ) #$(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBSLINU) -o $(NAME)

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
