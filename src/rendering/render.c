/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:29:43 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/05 15:31:48 by azarda           ###   ########.fr       */
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


unsigned int *ft_derection_render(t_global *pub, int i)
{
	t_derec de;
	unsigned int *tess;

	de.down = 0;
	de.up = 0;
	de.right = 0;
	de.left = 0;


	if (pub->info->player.ray[i].angle > 0 && pub->info->player.ray[i].angle < M_PI)
		de.down = 1;
	de.up = !de.down;
	if (pub->info->player.ray[i].angle < 0.5 * M_PI || pub->info->player.ray[i].angle > 1.5 * M_PI)
		de.right = 1;
	de.left = !de.right;
	if(de.down && pub->info->player.ray[i].flag == 1)
		tess = pub->img->WE.buffer_img;
	if(de.up && pub->info->player.ray[i].flag == 1)
		tess = pub->img->EA.buffer_img;
	if(de.left && pub->info->player.ray[i].flag == 2)
		tess = pub->img->SO.buffer_img;
	if(de.right && pub->info->player.ray[i].flag == 2)
		tess = pub->img->NO.buffer_img;

	return(tess);
}


void	to_3d_ray(t_global *pub)
{
	int ofset_x;
	int ofset_y;

	t_pos	pos;
	t_derec  der;


	int		start_y;
	int		end_y;
	int		alpha;

	// alpha = (double)((double)155 / HEIGHT) * (wp) + 100;



	int i = 0;
	int x = 0;
	int y = 0;


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
		// get_rgb(tess[((32 * ofset_y) + ofset_x)], tess[((32 * ofset_y) + ofset_x) + 1], tess[ ((32 * ofset_y) + ofset_x) + 2], tess[((32 * ofset_y) + ofset_x) + 3])


	while (i < WIDTH) {
		double wall_height = calcul_wp(&pub->info->player, i);

		unsigned int* tess = ft_derection_render(pub, i);






		if(pub->info->player.ray[i].flag == 1)
			ofset_x = (int)pub->info->player.ray[i].pos.x % SQUARE_LEN;
		else if (pub->info->player.ray[i].flag == 2)
			ofset_x = (int)pub->info->player.ray[i].pos.y % SQUARE_LEN;

		start_y = (HEIGHT / 2) - (wall_height / 2);
		if (start_y < 0)
			start_y = 0;
		end_y = (HEIGHT / 2) + (wall_height / 2);
		if (end_y > HEIGHT)
			end_y = HEIGHT;
		y = start_y;
		while (y < end_y) {
			ofset_y = (y + ((wall_height / 2) - (HEIGHT / 2))) * ((double)64 / wall_height);
			mlx_put_pixel_p(pub->window_img, i, y, (tess[(64 * ofset_y) + ofset_x]));
			y++;
		}
		i++;

	}

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
