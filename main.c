/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/02 21:58:04 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);	
}

t_global	*init_global(t_info *info)
{
	t_global	*global;

	global = (t_global *)malloc(sizeof(t_global));
	ft_error_ptr(global, 1);
	global->info = info;
	global->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!global->mlx)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	global->window_img = mlx_new_image(global->mlx, WIDTH, HEIGHT);
	if (!global->window_img)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	ft_error(mlx_image_to_window(global->mlx, global->window_img, 0, 0), 1);
	return (global);
}

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);
}

void	draw_square(t_global *pub, int x, int y, int color)
{
	int x_tmp;
	int y_tmp;
	
	x_tmp = x;
	y_tmp = y;
	while (y < (y_tmp + SQUARE_LEN))
	{
		x = x_tmp;
		while (x < (x_tmp + SQUARE_LEN))
		{
			printf("%d ---- %d\n", x, y);
			mlx_put_pixel(pub->window_img, x, y, color);
			x++;
		}
		y++;
	}
}

int	get_color(char c)
{
	if (c == '1'
		|| c == ' ')
		return (get_rgb(BLACK_R, BLACK_G, BLACK_B, 255));
	return (get_rgb(WHITE_R, WHITE_G, WHITE_B, 255));
}

void	to_2D_map(t_global *pub)
{
	t_pos	pos;
	t_pos	index;
	int		pos_s;
	int		color;

	pos_s = 50;
	pos.x = 0;
	pos.y = 0;

	index.x = -1;
	index.y = -1;
	while (pub->info->map[++index.y])
	{
		index.x = -1;
		while (pub->info->map[index.y][++index.x])
			draw_square(pub
				, index.x * SQUARE_LEN
				, index.y * SQUARE_LEN
				, get_color(pub->info->map[index.y][index.x]));
	}
}

void	cub3d(char *file_name)
{
	t_global	*pub;
	t_info		*info;

	info = parsing(file_name);
	pub = init_global(info);

	to_2D_map(pub);

	mlx_key_hook(pub->mlx, handle_keys, pub);

	mlx_loop(pub->mlx);
	mlx_terminate(pub->mlx);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}





// Parsing debug
// int debug_fd = open("Debug.log", O_RDWR);
// dprintf(debug_fd, "/* **************** */\n");
// dprintf(debug_fd, "/*     PARSING      */\n");
// dprintf(debug_fd, "/* **************** */\n");
// dprintf(debug_fd, "\nAttribute : \n");
// dprintf(debug_fd, "NO : %s \n", info->NO);
// dprintf(debug_fd, "SO : %s \n", info->SO);
// dprintf(debug_fd, "WE : %s \n", info->WE);
// dprintf(debug_fd, "EA : %s \n", info->EA);
// dprintf(debug_fd, "F : (%d,%d,%d) \n", info->F.r, info->F.g, info->F.b);
// dprintf(debug_fd, "C : (%d,%d,%d) \n", info->C.r, info->C.g, info->C.b);
// dprintf(debug_fd, "\nMap :\n");
// for (size_t i = 0; info->map[i]; i++)
// 	dprintf(debug_fd, "%s:newline\n", info->map[i]);
// printf("%sSUCCESS\n", GREEN);