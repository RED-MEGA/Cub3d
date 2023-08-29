/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/30 00:34:31 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_bp(char **map, t_pos pos)
{
	t_pos	tmp_pos;

	pos.x -= 5;
	pos.y -= 5;
	tmp_pos.x = pos.x;
	tmp_pos.y = pos.y;
	while (++pos.y <= (tmp_pos.y + 5))
	{
		pos.x = tmp_pos.x;
		while (++pos.x <= (tmp_pos.x + 5))
			if (map[(int)(pos.y / SQUARE_LEN)][(int)(pos.x / SQUARE_LEN)] == '1')
				return (false);
	}
	return (true);
}

void	get_new_pos(t_info *info, double rotation_angle)
{
	t_pos	new_pos;

	new_pos.x = info->player.pos.x;
	new_pos.y = info->player.pos.y;
	new_pos.x += cos(rotation_angle) * P_MOVE_SPEED;
	new_pos.y += sin(rotation_angle) * P_MOVE_SPEED;
	if (info->map[(int)(new_pos.y / SQUARE_LEN)][(int)(new_pos.x / SQUARE_LEN)] != '1'
		&& check_bp(info->map, new_pos))
	{
		info->player.pos.x = new_pos.x;
		info->player.pos.y = new_pos.y;
	}
}

void	set_newpos(t_global *pub)
{
	t_player	*player;
	t_pos		new_pos;
	double		rotation_angle;

	player = &(pub->info->player);
	if (player->turn_d != 0)
	{
		player->rotation_angle += (double)player->turn_d * P_ROTATION_SPEED;
		player->rotation_angle = normalize_angle(player->rotation_angle);
	}
	if (player->move_v != NONE)
	{
		rotation_angle = player->rotation_angle;
		if (player->move_v == UP)
			;
		else if (player->move_v == DOWN)
			rotation_angle += to_rad(180);
		get_new_pos(pub->info, rotation_angle);
	}
	if (player->move_h != NONE)
	{
		rotation_angle = player->rotation_angle;
		if (player->move_h == RIGHT)
			rotation_angle += to_rad(90);
		else if (player->move_h == LEFT)
			rotation_angle -= to_rad(90);
		get_new_pos(pub->info, rotation_angle);
	}
	printf("Turn : %d\n", player->turn_d);
	printf("Walk : %d\n", player->walk_d);
	printf("[ x: %.3f -- y: %.3f ]\n", player->pos.x, player->pos.y);
	printf("Rotation angle : %.3f\n\n", to_degree(player->rotation_angle));
}

void	handle_mouse(double xpos, double ypos, void* param)
{
	t_player	*player;

	player = (t_player *)param;
	if (xpos <= (WIDTH / 2) - (WIDTH / 8))
		player->turn_d = -1;
	else if (xpos >= (WIDTH / 2) + (WIDTH / 8))
		player->turn_d = 1;
	else
		player->turn_d = 0;
}

bool	key_press(mlx_key_data_t keydata, keys_t key)
{
	return (keydata.key == key
		&& (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT));
}

bool	key_release(mlx_key_data_t keydata, keys_t key)
{
	return (keydata.key == key
		&& keydata.action == MLX_RELEASE);
}

void	handle_moves(t_player *player, mlx_key_data_t keydata)
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
}

void	handle_turn(t_player *player, mlx_key_data_t keydata)
{
	if (key_press(keydata, MLX_KEY_RIGHT))
		player->turn_d = 1;
	else if (key_press(keydata, MLX_KEY_LEFT))
		player->turn_d = -1;
	else if (key_release(keydata, MLX_KEY_RIGHT))
		player->turn_d = 0;
	else if (key_release(keydata, MLX_KEY_LEFT))
		player->turn_d = 0;
}

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_global	*pub;
	t_player	*player;

	pub = (t_global *)param;
	player = &(pub->info->player);
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);
	handle_moves(player, keydata);
	handle_turn(player, keydata);
}
