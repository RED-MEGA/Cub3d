/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:29:43 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/13 14:48:45 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calcul_wp(t_player *player)
{
	double	a;
	double	b;
	double	d;

	a = (double)SQUARE_LEN;
	b = player->ray.len * cos(player->rotation_angle - player->ray.angle);
	d = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	return ((a / b) * d);
}

t_img	ft_img_render(t_global *pub)
{
	t_img	img;

	if (pub->de.down && pub->info->player.ray.flag == 1 \
	&& pub->info->player.ray.dor == 0)
		img = pub->info->SO;
	else if (pub->de.up && pub->info->player.ray.flag == 1 \
	&& pub->info->player.ray.dor == 0)
		img = pub->info->NO;
	else if (pub->de.left && pub->info->player.ray.flag == 2 \
	&& pub->info->player.ray.dor == 0)
		img = pub->info->EA;
	else if (pub->de.right && pub->info->player.ray.flag == 2 \
	&& pub->info->player.ray.dor == 0)
		img = pub->info->WE;
	else
		img = pub->info->DOOR;
	return (img);
}

int	calcul_ofset_x(t_ray ray, t_img img)
{
	int	ofset_x;

	if (ray.flag == 1)
		ofset_x = (ray.pos.x / SQUARE_LEN - \
		(int)ray.pos.x / SQUARE_LEN) * img.width;
	else if (ray.flag == 2)
		ofset_x = (ray.pos.y / SQUARE_LEN - \
		(int)ray.pos.y / SQUARE_LEN) * img.width;
	return (ofset_x);
}

void	to_3d_ray(t_global *pub, int i, double wall_height, int y)
{
	t_img	img;
	int		ofset_x;
	int		ofset_y;
	int		start_y;
	int		end_y;

	img = ft_img_render(pub);
	ofset_x = calcul_ofset_x(pub->info->player.ray, img);
	start_y = (HEIGHT / 2) - (wall_height / 2);
	end_y = (HEIGHT / 2) + (wall_height / 2);
	// if (end_y > HEIGHT)
	// 	end_y = HEIGHT; // !cheak Not work
	while (++y < HEIGHT)
	{
		if (y < start_y)
			draw_fc(pub->window_img, pub->info->C, (t_pos){.x = i, .y = y});
		else if (y >= start_y && y < end_y)
		{
			ofset_y = (y - start_y) * ((double)img.height / wall_height);
			mlx_put_pixel_p(pub->window_img, i, y, \
			(img.buffer_img[(img.width * ofset_y) + ofset_x]));
		}
		else if (y > end_y)
			draw_fc(pub->window_img, pub->info->F, (t_pos){.x = i, .y = y});
	}
}
