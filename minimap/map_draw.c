/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:04:16 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/29 06:09:14 by reben-ha         ###   ########.fr       */
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
		return (get_rgb(101, 69, 31, 255));
	return (get_rgb(BLACK_R, BLACK_G, BLACK_B, 255));
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
	for (size_t i = 0; i < WIDTH; i++)
		draw_line(pub->window_img, player->pos, player->ray[i].pos);
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

void	draw_flex_map(mlx_image_t *image, t_info *info)
{
	t_pos	map_pos;
	t_pos	pos_tmp;
	t_pos	pos;
	int		color;

	map_pos = info->player.pos;
	map_pos.y -= MINIMAP_SIZE / 2;
	map_pos.x -= MINIMAP_SIZE / 2;
	pos_tmp = map_pos;
	pos.x = 0;
	pos.y = 0;
	while (map_pos.y < (pos_tmp.y + MINIMAP_SIZE))
	{
		pos.x = 0;
		map_pos.x = pos_tmp.x;
		while (map_pos.x < (pos_tmp.x + MINIMAP_SIZE))
		{
			if ((map_pos.x >= 0 && map_pos.y >= 0)
					&& (map_pos.y < info->map_p_size.y && map_pos.x < info->map_p_size.x))
				color = get_color(info->map[(int)map_pos.y / SQUARE_LEN][(int)map_pos.x / SQUARE_LEN]);
			else
				color = get_color('1');
			mlx_put_pixel_p(image
					, pos.x, pos.y, color);
			map_pos.x++;
			pos.x++;
		}
		map_pos.y++;
		pos.y++;
	}
}

void	draw_rotation(mlx_image_t *image, t_player *player)
{
	t_pos	end;

	end.x = (MINIMAP_SIZE / 2) + (cos(player->rotation_angle) * 23);
	end.y = (MINIMAP_SIZE / 2) + (sin(player->rotation_angle) * 23);
	draw_line(image, (t_pos){.x = MINIMAP_SIZE / 2, .y = MINIMAP_SIZE / 2}, end);
}

void	minimap(t_global *pub)
{
	t_player	*player;

	player = &pub->info->player;
	draw_flex_map(pub->window_img, pub->info);
	draw_player(pub->window_img, pub->info);
	draw_rotation(pub->window_img, player);
}
