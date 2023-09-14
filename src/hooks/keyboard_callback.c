/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_callback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:34:27 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/14 14:51:47 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	handle_turn(t_player *player, mlx_key_data_t keydata)
{
	if (key_press(keydata, MLX_KEY_RIGHT))
		player->turn_d = 1;
	else if (key_press(keydata, MLX_KEY_LEFT))
		player->turn_d = -1;
	else if (key_release(keydata, MLX_KEY_RIGHT))
		player->turn_d = 0;
	else if (key_release(keydata, MLX_KEY_LEFT))
		player->turn_d = 0;
	else
		return (false);
	return (true);
}

bool	handle_moves(t_player *player, mlx_key_data_t keydata)
{
	if (key_press(keydata, MLX_KEY_W))
		player->move_v = UP;
	else if (key_press(keydata, MLX_KEY_S))
		player->move_v = DOWN;
	else if (key_release(keydata, MLX_KEY_W))
		player->move_v = NONE;
	else if (key_release(keydata, MLX_KEY_S))
		player->move_v = NONE;
	else if (key_press(keydata, MLX_KEY_D))
		player->move_h = RIGHT;
	else if (key_press(keydata, MLX_KEY_A))
		player->move_h = LEFT;
	else if (key_release(keydata, MLX_KEY_D))
		player->move_h = NONE;
	else if (key_release(keydata, MLX_KEY_A))
		player->move_h = NONE;
	else
		return (false);
	return (true);
}

bool	handle_features(t_global *pub, mlx_key_data_t keydata)
{
	if (mlx_is_key_down(pub->mlx, MLX_KEY_O))
		return (open_door(pub), true);
	if (mlx_is_key_down(pub->mlx, MLX_KEY_C))
		return (close_door(pub), true);
	if (keydata.key == MLX_KEY_LEFT_SHIFT)
	{
		if (key_press(keydata, MLX_KEY_LEFT_SHIFT))
			pub->info->player.sprint = true;
		else if (key_release(keydata, MLX_KEY_LEFT_SHIFT))
			pub->info->player.sprint = false;
		return (true);
	}
	if (key_press(keydata, MLX_KEY_F))
	{
		if (pub->mode == MLX_MOUSE_HIDDEN)
			pub->mode = MLX_MOUSE_NORMAL;
		else
			pub->mode = MLX_MOUSE_HIDDEN;
		mlx_set_cursor_mode(pub->mlx, pub->mode);
		return (true);
	}
	return (false);
}

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_global	*pub;

	pub = (t_global *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		destroy_global(pub);
	if (handle_features(pub, keydata))
		return ;
	if (handle_moves(&pub->info->player, keydata))
		return ;
	if (handle_turn(&pub->info->player, keydata))
		return ;
}
