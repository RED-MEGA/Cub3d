/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:29:43 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/25 18:56:43 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calculate 3d len_projection
/*
note 1:
	len_projection = (
		Square len / $ray_l3abd
		 * 
		((Width / 2) / tan(FOV / 2)))

note 2:
	START POS FOR DRAW = (
		(HIGTH / 2) - ($len_projection / 2)
	)
*/
double	calcul_wp(t_player	*player, int i)
{
	// note 1:
	return (
		SQUARE_LEN / (player->ray[i].len * cos(player->ray[i].ray_angle))
		*
		((WIDTH / 2) / tan(FOV_ANGLE / 2))
	);
}

//  #765127 has RGB values of R:118, G:81, B:39

void	to_3d_ray(mlx_image_t *image, double wp, int i)
{
	t_pos	pos;
	int		end_y;

	pos.x = i;
	pos.y = (HEIGHT / 2) - (wp / 2);
	end_y = (HEIGHT / 2) + (wp / 2);
	while (pos.y < end_y)
	{
		mlx_put_pixel_p(image
			, pos.x, pos.y
			, get_rgb(12, 53, 106, 255));
		pos.y++;
	}
}

void	render(t_global *pub)
{
	double	wp;

	for (size_t i = 0; i < WIDTH; i++)
	{
		wp = calcul_wp(&pub->info->player, i);
		to_3d_ray(pub->window_img, wp, i);
	}
}
