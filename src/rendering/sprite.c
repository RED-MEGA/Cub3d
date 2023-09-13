/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 23:43:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/13 21:39:17 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_image(mlx_image_t *image, int x, int y, mlx_texture_t *texture)
{
	int	x_tmp;
	int	y_tmp;
	int	i;
	int	color;

	i = 0;
	x_tmp = x;
	y_tmp = y;
	while (y < (y_tmp + texture->height))
	{
		x = x_tmp;
		while (x < (x_tmp + texture->width))
		{
			color = get_rgb(texture->pixels[i],
					texture->pixels[i + 1], texture->pixels[i + 2], 255);
			if (color != 255)
				mlx_put_pixel_p(image, x, y, color);
			i += texture->bytes_per_pixel;
			x++;
		}
		y++;
	}
}

void	animated_sprite(mlx_image_t *image, t_info *info, int x)
{
	static unsigned char	i;

	if ((i / 3) == 0)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	else if ((i / 3) == 1)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	else if ((i / 3) == 2)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	else if ((i / 3) == 3)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	else if ((i / 3) == 4)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	else if ((i / 3) == 5)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	else if ((i / 3) == 6)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	else if ((i / 3) == 7)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	else if ((i / 3) == 8)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	else if ((i / 3) == 9)
		draw_image(image, x, 0, info->sprite[(i / 3)]);
	i++;
	if (i >= (9 * 3))
		i = 0;
}

void	mjollnir(t_global *pub)
{
	int	y;
	int	x;
	int	frame_i;

	frame_i = 0;
	if (pub->info->player.attack == true)
	{
		x = (WIDTH / 2) - (pub->info->sprite[0]->width / 2);
		animated_sprite(pub->window_img, pub->info, x);
		frame_i = 1;
	}
	x = (WIDTH / 2) - (pub->info->weapon[frame_i]->width / 2);
	y = HEIGHT - pub->info->weapon[frame_i]->height;
	draw_image(pub->window_img, x, y, pub->info->weapon[frame_i]);
}
