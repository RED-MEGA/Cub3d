/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/05 20:08:08 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	refresh_frame(t_global *pub)
{
	t_player	*player;

	player = &(pub->info->player);
	if (player->turn_d != 0)
		player->rotation_angle += (double)player->turn_d * (5 * (M_PI / 180));
	printf("Turn : %d\n", player->turn_d);
	printf("  |\n");
	printf("   - rotation angle : %f\n\n", player->rotation_angle);


	if (player->walk_d != 0)
	{	
		player->pos.x += cos(player->rotation_angle) * (player->walk_d * P_MOVE_SPEED);
		player->pos.y += sin(player->rotation_angle) * (player->walk_d * P_MOVE_SPEED);
	}
	printf("Walk : %d\n", player->walk_d);
	printf("  |\n");
	printf("   - rotation angle : %f\n\n", player->rotation_angle);

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
