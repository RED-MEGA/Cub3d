/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:09:18 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/24 20:13:29 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fc(t_global *pub)
{
	t_pos	pos;

	pos.y = -1;
	while (++pos.y < HEIGHT)
	{
		pos.x = -1;
		while (++pos.x < WIDTH)
		{
			if (pos.y >= 0 && pos.y <= HEIGHT / 2)
				mlx_put_pixel_p(pub->window_img,
					pos.x, pos.y,
					get_rgb(pub->info->C.r,
						pub->info->C.g,
						pub->info->C.b,
						255));

			if (pos.y >= HEIGHT / 2 && pos.y <= HEIGHT)
				mlx_put_pixel_p(pub->window_img,
					pos.x, pos.y,
					get_rgb(pub->info->F.r,
						pub->info->F.g,
						pub->info->F.b,
						255));
		}
	}
}
