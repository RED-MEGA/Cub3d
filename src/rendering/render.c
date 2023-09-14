/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:29:43 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/14 19:04:03 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fc(mlx_image_t *image, t_color color, t_pos pos)
{
	mlx_put_pixel_p(image, pos.x, pos.y,
		get_rgb(color.r, color.g, color.b, 255));
}

void	render(t_global *pub)
{
	t_player	*player;
	t_loc		range;
	double		wall_height;
	int			i;

	i = -1;
	player = &(pub->info->player);
	player->ray_angle = normalize_angle(player->rotation_angle
			- (FOV_ANGLE / 2));
	while (++i < WIDTH)
	{
		calcul_ray(pub, player);
		wall_height = calcul_wp(player);
		range.i = (HEIGHT / 2) - (wall_height / 2);
		range.j = (HEIGHT / 2) + (wall_height / 2);
		to_3d_ray(pub, i, wall_height, &range);
		player->ray_angle = normalize_angle(player->ray_angle + RAY_D);
		player->ray.dor = 0;
	}
}
