/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 23:43:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/12 23:43:38 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_image(mlx_image_t *image, int x, int y, mlx_texture_t *texture)
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
			color = get_rgb(texture->pixels[i], texture->pixels[i + 1], texture->pixels[i + 2], 255);
			if (color != 255)
				mlx_put_pixel_p(image, x, y, color);
			i += texture->bytes_per_pixel;
			x++;
		}
		y++;
	}
}

void animated_sprite(t_global *pub)
{
	t_info					*info;
	int						x;
	int						y;
	static unsigned char	i;
	unsigned char	repeat = 3;


	info = (t_info *)pub->info;
	x = (WIDTH / 2) - (info->sprite[0]->width / 2);
	y = 0;
	if ((i / repeat) == 0)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 1)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 2)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 3)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 4)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 5)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 6)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 7)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 8)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 9)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	i++;
	if (i >= (9 * repeat))
		i = 0;
}

void	mjollnir(t_global *pub)
{
	int y;
	int x;
	int	frame_i;

	frame_i = 0;
	if (pub->info->player.attack == true)
	{
		animated_sprite(pub);
		frame_i = 1;
	}
	x = (WIDTH / 2) - (pub->info->weapon[frame_i]->width / 2);
	y = HEIGHT - pub->info->weapon[frame_i]->height;
	draw_image(pub->window_img, x, y, pub->info->weapon[frame_i]);
}
