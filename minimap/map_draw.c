/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:04:16 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/25 16:22:50 by reben-ha         ###   ########.fr       */
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

void	draw_square(mlx_image_t *image, int x, int y, int color)
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
			mlx_put_pixel_p(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_fov(t_global *pub, t_player *player)
{
	t_pos		end_pos;

	player->ray_angle = normalize_angle(player->rotation_angle - (FOV_ANGLE / 2));
	for (size_t i = 0; i < WIDTH; i++)
	{
		end_pos = ray_cast(pub);
		player->ray[i].ray_angle = player->ray_angle;
		player->ray[i].len = draw_line(pub->window_img, player->pos, end_pos);
		player->ray_angle = normalize_angle(player->ray_angle + RAY_D);
	}
}

void	draw_map(t_global *pub)
{
	t_loc	index;

	index.j = -1;
	index.i = -1;
	while (pub->info->map[++index.i])
	{
		index.j = -1;
		while (pub->info->map[index.i][++index.j])
			draw_square(pub->window_img
				, index.j * SQUARE_LEN
				, index.i * SQUARE_LEN
				, get_color(pub->info->map[index.i][index.j]));
	}
}

void	minimap(t_global *pub)
{
	t_player	*player;

	player = &pub->info->player;
	draw_map(pub);
	draw_player(pub->window_img, pub->info);
	draw_fov(pub, player);
}
