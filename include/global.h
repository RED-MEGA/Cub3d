/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:06 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/03 04:22:33 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>
# include <time.h>
# include "MLX42/MLX42.h"

# define ERROR  "\033[31;1mError :\033[0m "
# define FAIL -1
# define SUCCESS 0

# define ERRMALLOC "Cannot allocate memory"
# define ERRFORK "Failed to fork process"
# define ERRPERMISSION "Permission denied"
# define ERRINVALID "Invalid argument"
# define ERRFILE "Invalid file"
# define ERREMPTY "Empty file"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# define RED_R 255
# define RED_G 0
# define RED_B 0
# define BLACK_R 0
# define BLACK_G 0
# define BLACK_B 0
# define WHITE_R 255
# define WHITE_G 255
# define WHITE_B 255

# define HEIGHT 1080
# define WIDTH 1920

# define SQUARE_LEN 50

# define MINIMAP_SIZE (WIDTH / 6)

# define P_RADIUS (SQUARE_LEN / 4)
# define P_ROTATION_SPEED 2.0 * (M_PI / 180)
# define P_MOVE_SPEED 3.0

# define PI M_PI
# define RAY_D (FOV_ANGLE / WIDTH)
# define FOV_ANGLE (60 * (PI / 180))

typedef enum e_direction
{
	NO,
	SO,
	WE,
	EA
}	e_direction;

typedef enum e_move
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
}	e_move;

typedef struct s_list
{
	char			*data;
	int				len;
	int				index;
	struct s_list	*next;
}	t_list;

typedef struct s_pos
{
	double x;
	double y;
}	t_pos;

typedef struct s_loc
{
	int	j;
	int	i;
}	t_loc;

typedef struct s_ray
{
	double	angle;
	double	len;
	t_pos	pos;
	int flag;
}	t_ray;

typedef struct s_player
{
	t_pos		pos;
	e_direction	direction;
	e_move		move_h;
	e_move		move_v;
	int			turn_d;
	int			walk_d;
	int			move_d;
	double		rotation_angle;
	double		ray_angle;
	t_ray		ray[WIDTH];
	char		key;
	bool		sprint;
}	t_player;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct  s_img_data
{
	// char			*path;
	uint32_t		heith;
	uint32_t		whidet;
	unsigned int	*buffer_img;

}	t_img;

typedef struct  s_pixel
{
	t_img	NO;
	t_img	SO;
	t_img	WE;
	t_img	EA;
} t_pixel;

typedef struct s_info
{
	t_player	player;
	t_color		F;
	t_color		C;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		**map;
	int			s_y_map;
	int			s_x_map;
	t_pos		map_p_size;
	t_loc		map_m_size;
}	t_info;


typedef struct  s_derec
{
	int	down;
	int	up;
	int	right;
	int	left;
} t_derec;


typedef struct s_global
{
	t_info		*info;
	mlx_t		*mlx;
	mlx_image_t	*window_img;
	t_derec		de;
	t_pixel *img;

}	t_global;


#endif
