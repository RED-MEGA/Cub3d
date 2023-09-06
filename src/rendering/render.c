/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:29:43 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/06 01:17:36 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calcul_wp(t_player *player, int i)
{
	double	A;
	double	B;
	double	D;

	A = (double)SQUARE_LEN;
	B = player->ray.len * cos(player->rotation_angle - player->ray.angle);
	D = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	return ((A / B) * D);
}

// get_rgb(255, 245, 224, alpha)


t_img ft_derection_render(t_global *pub, int i)
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
	if(de.down && pub->info->player.ray.flag == 1)
		img = pub->img->WE;
	if(de.up && pub->info->player.ray.flag == 1)
		img = pub->img->EA;
	if(de.left && pub->info->player.ray.flag == 2)
		img = pub->img->SO;
	if(de.right && pub->info->player.ray.flag == 2)
		img = pub->img->NO;
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



	// alpha = (double)((double)155 / HEIGHT) * (wp) + 100;

	// for (int i = 0; i < HEIGHT; i++){
	// 	for (int j = 0; j < WIDTH ; j++)
	// 	{
	// 		if (i > (HEIGHT / 2)){
	// 			mlx_put_pixel(pub->window_img, j, i, get_rgb(pub->info->C.r, pub->info->C.g, pub->info->C.b, 255));
	// 		}
	// 		else {
	// 			mlx_put_pixel(pub->window_img, j, i, get_rgb(pub->info->F.r, pub->info->F.g, pub->info->F.b, 255));
	// 		}
	// 	}
	// }


	t_img img = ft_derection_render(pub, i);

	// hprisontal flag ==   1




	if(pub->info->player.ray.flag == 1)
	{
		if(pub->info->player.ray.dor)
			ofset_x = (pub->info->player.ray.pos.x / SQUARE_LEN - (int)pub->info->player.ray.pos.x / SQUARE_LEN) * pub->img->DOR.whidet;
		else
			ofset_x = (pub->info->player.ray.pos.x / SQUARE_LEN - (int)pub->info->player.ray.pos.x / SQUARE_LEN) * img.whidet;
	}


	else if (pub->info->player.ray.flag == 2)
	{
		if(pub->info->player.ray.dor)
			ofset_x = (pub->info->player.ray.pos.y / SQUARE_LEN - (int)pub->info->player.ray.pos.y / SQUARE_LEN) * pub->img->DOR.whidet;
		else
			ofset_x = (pub->info->player.ray.pos.y / SQUARE_LEN - (int)pub->info->player.ray.pos.y / SQUARE_LEN) * img.whidet;
	}

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
			if(pub->info->player.ray.dor && pub->info->player.ray.flag == 1)
			{
				ofset_y = (y - start_y) * ((double)pub->img->DOR.heith / wall_height);
				mlx_put_pixel_p(pub->window_img, i, y, (pub->img->DOR.buffer_img[(pub->img->DOR.whidet * ofset_y) + ofset_x]));
				// pub->info->player.ray.dor = 0;
			}
			else if ( pub->info->player.ray.dor == 0)
			{
				ofset_y = (y - start_y) * ((double)img.heith / wall_height);
				mlx_put_pixel_p(pub->window_img, i, y, (img.buffer_img[(img.whidet * ofset_y) + ofset_x]));\
			}
		}
		else if (y > end_y)
			draw_fc(pub->window_img, pub->info->F, (t_pos) {.x = i, .y = y});
	}
}

void	render(t_global *pub)
{
	// double	wp;
	// int		i;

	// i = -1;
	// while (++i < WIDTH)
	// {
	// 	wp = calcul_wp(&pub->info->player, i);
	// 	to_3d_ray(pub, i, wp);
	// }
}
