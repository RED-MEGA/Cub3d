/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:47:56 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/13 19:13:27 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(mlx_image_t *image)
{
	t_pos	pos;
	t_pos	center_pos;
	int		distance;

	center_pos.x = MINIMAP_SIZE / 2;
	center_pos.y = MINIMAP_SIZE / 2;
	pos.y = -1;
	pos.x = -1;
	while (++pos.y < MINIMAP_SIZE)
	{
		pos.x = -1;
		while (++pos.x < MINIMAP_SIZE)
		{
			distance = calcul_distance(center_pos, pos);
			if (distance < P_RADIUS)
				mlx_put_pixel_p(image, pos.x, pos.y,
					get_rgb(RED_R, RED_G, RED_B, 255));
		}
	}
}
