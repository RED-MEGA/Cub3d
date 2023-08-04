/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/04 20:59:41 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_global	*pub;
	t_player	*player;

	pub = (t_global *)param;
	player = &(pub->info->player);
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		player->turn_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		player->turn_d = -1;
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		player->walk_d = 1;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		player->walk_d = -1;




	player->pos.x += cos(player->rotation_angle) * (player->walk_d * P_MOVE_SPEED);
	player->pos.y += sin(player->rotation_angle) * (player->walk_d * P_MOVE_SPEED);


	player->rotation_angle += (double)player->turn_d * (2 * (M_PI / 180));
	// printf("rotation angle : %f\n", player->rotation_angle);
	// printf("turn : %d\n", player->turn_d);


	to_2D_map(pub);
	player->turn_d = 0;
	player->walk_d = 0;
}
