/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:04:16 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/02 22:06:59 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	get_color(char c)
{
	if (c == '1'
		|| c == ' ')
		return (get_rgb(BLACK_R, BLACK_G, BLACK_B, 255));
	return (get_rgb(WHITE_R, WHITE_G, WHITE_B, 255));
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

void	to_2D_map(t_global *pub)
{
	t_pos	index;

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
