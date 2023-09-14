/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:04:16 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/14 15:35:07 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(char c)
{
	if (c == '1' || c == ' ')
		return (get_rgb(109, 93, 110, 255));
	else if (c == 'D')
		return (get_rgb(79, 112, 156, 255));
	else if (c == 'd')
		return (get_rgb(33, 53, 85, 255));
	return (get_rgb(0, 0, 0, 255));
}

int	select_color_map(t_info *info, t_pos *map_pos)
{
	int	color;

	if ((map_pos->x >= 0 && map_pos->y >= 0)
		&& (map_pos->y < info->map_p_size.y
			&& map_pos->x < info->map_p_size.x))
		color = get_color(info->map[(int)map_pos->y / SQUARE_LEN]
			[(int)map_pos->x / SQUARE_LEN]);
	else
		color = get_color('1');
	return (color);
}

void	draw_dynamic_map(mlx_image_t *image, t_info *info)
{
	t_pos	map_pos;
	t_pos	pos_tmp;
	t_pos	pos;

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
			mlx_put_pixel_p(image, pos.x, pos.y,
				select_color_map(info, &map_pos));
			map_pos.x++;
			pos.x++;
		}
		map_pos.y++;
		pos.y++;
	}
}

void	minimap(t_global *pub)
{
	t_player	*player;

	player = &pub->info->player;
	draw_dynamic_map(pub->window_img, pub->info);
	draw_player(pub->window_img);
}
