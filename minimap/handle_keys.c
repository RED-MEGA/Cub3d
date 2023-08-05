/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/05 21:25:17 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	refresh_frame(void *param)
{
	t_global	*pub;
	t_player	*player;
	t_pos		new_pos;

	pub = (t_global *)param;
	player = &(pub->info->player);


	if (player->turn_d != 0)
		player->rotation_angle += (double)player->turn_d * (5 * (M_PI / 180));


	if (player->walk_d != 0)
	{
		new_pos.x = player->pos.x;
		new_pos.y = player->pos.y;
		new_pos.x += cos(player->rotation_angle) * (player->walk_d * P_MOVE_SPEED);
		new_pos.y += sin(player->rotation_angle) * (player->walk_d * P_MOVE_SPEED);
		if (pub->info->map[(int)(new_pos.y / SQUARE_LEN)][(int)(new_pos.x / SQUARE_LEN)] != '1')
		{
			player->pos.x = new_pos.x;
			player->pos.y = new_pos.y;
		}
	}



	printf("Turn : %d\n", player->turn_d);
	printf("Walk : %d\n", player->walk_d);
	printf("[ x: %d -- y: %d ]\n", player->pos.x, player->pos.y);
	printf("Rotation angle : %f\n\n", player->rotation_angle);
	// update frame
	to_2D_map(pub);
}

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_global	*pub;
	t_player	*player;

	pub = (t_global *)param;
	player = &(pub->info->player);
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);

	if (keydata.key == MLX_KEY_UP
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->walk_d = 1;
	else if (keydata.key == MLX_KEY_DOWN
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->walk_d = -1;
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		player->walk_d = 0;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		player->walk_d = 0;
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turn_d = 1;
	else if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->turn_d = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		player->turn_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		player->turn_d = 0;
}
