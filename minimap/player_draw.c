/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:47:56 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/04 15:48:11 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(mlx_image_t *image, t_info *info)
{
	t_pos	pos;
	int		distance;

	pos.y = -1;
	pos.x = -1;
	while (++pos.y < info->map_size.y)
	{
		pos.x = -1;
		while (++pos.x < info->map_size.x)
		{
			distance = sqrt(pow(info->player.pos.x - pos.x, 2)
					 + pow(info->player.pos.y - pos.y, 2));
			if (distance < P_RADIUS)
				mlx_put_pixel(image
						, pos.x, pos.y
						, get_rgb(RED_R, RED_G, RED_B, 255));
		}
	}
}
