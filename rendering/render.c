/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:29:43 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/02 21:58:32 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calcul_wp(t_player *player, int i)
{
	double	A;
	double	B;
	double	D;

	A = (double)SQUARE_LEN;
	B = player->ray[i].len * cos(player->rotation_angle - player->ray[i].angle);
	D = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	return ((A / B) * D);
}

// get_rgb(255, 245, 224, alpha)




void	to_3d_ray(t_global *pub)
{
	int ofset_x;
	int ofset_y;

	t_pos	pos;
	int		start_y;
	int		end_y;
	int		alpha;

	// alpha = (double)((double)155 / HEIGHT) * (wp) + 100;



	int i = 0;
	int x = 0;
	int y =0;


	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDTH ; j++)
		{
			if (i > (HEIGHT / 2)){
				mlx_put_pixel(pub->window_img, j, i, get_rgb(pub->info->C.r, pub->info->C.g, pub->info->C.b, 255));
			}
			else {
				mlx_put_pixel(pub->window_img, j, i, get_rgb(pub->info->F.r, pub->info->F.g, pub->info->F.b, 255));
			}
		}
	}

	while (i < WIDTH) {
		double wall_height = calcul_wp(&pub->info->player, i);

		unsigned int* tess;

		if(pub->info->player.ray[i].flag == 1)
		{
			ofset_x = (int)pub->info->player.ray[i].pos.x % SQUARE_LEN;
			tess = pub->img->EA;
		}
		else if (pub->info->player.ray[i].flag == 2)
		{
			ofset_x = (int)pub->info->player.ray[i].pos.y % SQUARE_LEN;
			tess = pub->img->WE;
		}
		start_y = (HEIGHT / 2) - (wall_height / 2);
		if (start_y < 0)
			start_y = 0;
		end_y = (HEIGHT / 2) + (wall_height / 2);
		if (end_y > HEIGHT)
			end_y = HEIGHT;
		y = start_y;
		while (y < end_y) {
			ofset_y = (y + ((wall_height / 2) - (HEIGHT / 2))) * ((float)64 / wall_height);
			mlx_put_pixel_p(pub->window_img, i, y, (tess[(64 * ofset_y) + ofset_x]));
			y++;
		}
		i++;

	}

	// (offset_y* texture->line_length + offset_x
	// * (texture->bits_per_pixel / 8))

	// int tess;
	// int k;
	// int y;



	// while (pos.y < HEIGHT)
	// {
	// 	if (pos.y < start_y)
	// 		draw_fc(image, info->C, pos);



	// 	else if (pos.y >= start_y && pos.y <= end_y)
	// 	{
	// 		if(flag)
	// 			ofset_x = (int)pub->tess_y % SQUARE_LEN;
	// 		else
	// 			ofset_x = (int)pub->tess_x % SQUARE_LEN;


	// 		y = start_y;
	// 		while(y < end_y)
	// 		{
	// 			int destenc = (y + (wp / 2) - (HEIGHT / 2));
	// 			ofset_y = destenc * (50 / wp);

	// 			printf("ofset_y  -> %d\n", ofset_y);

	// 			k = pub->img->EA[(50 * ofset_y) + ofset_x];

	// 			printf("k  -> %d\n", k);

	// 		 	tess = pub->img->EA[(WIDTH * y) + i] = k;
	// 			// exit(0);
	// 			mlx_put_pixel_p(image, pos.x, y , tess);
	// 			y++;
	// 		}
	// 	}




	// 	else if (pos.y > end_y)
			// draw_fc(image, info->F, pos);
	// 	pos.y++;
	// }
}

void	render(t_global *pub)
{
	double	wp;

	// for (size_t i = 0; i < WIDTH; i++)
	// {
		// wp = calcul_wp(&pub->info->player, i);
		to_3d_ray(pub);
	// }
}
