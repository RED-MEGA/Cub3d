/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:29:43 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/09 21:17:56 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calcul_wp(t_player *player)
{
	double	A;
	double	B;
	double	D;

	A = (double)SQUARE_LEN;
	B = player->ray.len * cos(player->rotation_angle - player->ray.angle);
	D = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	return ((A / B) * D);
}



t_img ft_derection_render(t_global *pub)
{
	t_derec de;
	t_img img;

	de.down = 0;
	de.up = 0;
	de.right = 0;
	de.left = 0;


	if (pub->info->player.ray.angle > 0 && pub->info->player.ray.angle < M_PI)
		de.down = 1;
	de.up = !de.down;
	if (pub->info->player.ray.angle < 0.5 * M_PI || pub->info->player.ray.angle > 1.5 * M_PI)
		de.right = 1;
	de.left = !de.right;
	if (de.down && pub->info->player.ray.flag == 1 && pub->info->player.ray.dor == 0)
			img = pub->info->WE;
	else if  (de.up && pub->info->player.ray.flag == 1 && pub->info->player.ray.dor == 0)
			img = pub->info->EA;
	else if  (de.left && pub->info->player.ray.flag == 2 && pub->info->player.ray.dor == 0)
			img = pub->info->SO;
	else if  (de.right && pub->info->player.ray.flag == 2 && pub->info->player.ray.dor == 0)
			img = pub->info->NO;
	else
		img = pub->info->DOOR;
	return(img);
}

void	to_3d_ray(t_global *pub, int i, double wall_height)
{
	int ofset_x;
	int ofset_y;

	t_pos	pos;
	t_derec  der;
	int		start_y;
	int		end_y;
	int		alpha;




	t_img img = ft_derection_render(pub);





	if(pub->info->player.ray.flag == 1)
			ofset_x = (pub->info->player.ray.pos.x / SQUARE_LEN - (int)pub->info->player.ray.pos.x / SQUARE_LEN) * img.width;
	else if (pub->info->player.ray.flag == 2)
			ofset_x = (pub->info->player.ray.pos.y / SQUARE_LEN - (int)pub->info->player.ray.pos.y / SQUARE_LEN) * img.width;

	start_y = (HEIGHT / 2) - (wall_height / 2);
	// if (start_y < 0)
	// 	start_y = 0;  // !cheakk
	end_y = (HEIGHT / 2) + (wall_height / 2);
	if (end_y > HEIGHT)
		end_y = HEIGHT;


	int y = -1;
	while (++y < HEIGHT)
	{
		if (y < start_y)
			draw_fc(pub->window_img, pub->info->C, (t_pos) {.x = i, .y = y});
		else if (y >= start_y && y < end_y)
		{
			ofset_y = (y - start_y) * ((double)img.height / wall_height);
			mlx_put_pixel_p(pub->window_img, i, y, (img.buffer_img[(img.width * ofset_y) + ofset_x]));\
		}
		else if (y > end_y)
			draw_fc(pub->window_img, pub->info->F, (t_pos) {.x = i, .y = y});
	}
}

