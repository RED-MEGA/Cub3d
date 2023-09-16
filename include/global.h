/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:06 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/16 18:59:46 by reben-ha         ###   ########.fr       */
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

# define ERRINVALID "Invalid argument"
# define ERRFILE "Invalid file"
# define ERREMPTY "Empty file"

# define HEIGHT 1080
# define WIDTH 1920

# define SQUARE_LEN 64
# define MINIMAP_SIZE 320
# define P_RADIUS 16

typedef enum t_direction
{
	NO,
	SO,
	WE,
	EA
}	t_direction;

typedef enum t_move
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
}	t_move;

typedef struct s_list
{
	char			*data;
	int				len;
	int				index;
	struct s_list	*next;
}	t_list;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_doubl
{
	t_pos	a;
	t_pos	b;
}	t_doubl;

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
	int		flag;
	int		dor;
}	t_ray;

typedef struct s_player
{
	t_pos		pos;
	t_direction	direction;
	t_move		move_h;
	t_move		move_v;
	int			turn_d;
	double		rotation_angle;
	double		ray_angle;
	t_ray		ray;
	char		key;
	bool		sprint;
	bool		attack;
}	t_player;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_img_data
{
	char			*path;
	uint32_t		height;
	uint32_t		width;
	unsigned int	*buffer_img;
}	t_img;

typedef struct s_info
{
	t_player		player;
	t_color			F;
	t_color			C;
	t_img			NO;
	t_img			SO;
	t_img			WE;
	t_img			EA;
	t_img			DOOR;
	char			**map;
	t_pos			map_p_size;
	t_loc			map_m_size;
	mlx_texture_t	*weapon[2];
	mlx_texture_t	*sprite[10];
}	t_info;

typedef struct s_derec
{
	bool	down;
	bool	up;
	bool	right;
	bool	left;
}	t_derec;

typedef struct s_global
{
	t_info			*info;
	mlx_t			*mlx;
	mlx_image_t		*window_img;
	t_derec			de;
	mouse_mode_t	mode;
}	t_global;

#endif
