/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/02 21:59:56 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	wall_collision(char **map, t_pos oldpos, t_pos newpos)
{
	if (map[(int)(newpos.y / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != '1'
		&& map[(int)((newpos.y + P_RADIUS) / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != '1'
		&& map[(int)((newpos.y - P_RADIUS) / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != '1'
		&& map[(int)(newpos.y / SQUARE_LEN)][(int)((newpos.x + P_RADIUS) / SQUARE_LEN)] != '1'
		&& map[(int)(newpos.y / SQUARE_LEN)][(int)((newpos.x - P_RADIUS) / SQUARE_LEN)] != '1'
		&& map[(int)(oldpos.y / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != '1'
		&& map[(int)(newpos.y / SQUARE_LEN)][(int)(oldpos.x / SQUARE_LEN)] != '1')
		return (true);
	return (false);
}

void	get_new_pos(t_info *info, double rotation_angle)
{
	t_pos	new_pos;

	new_pos.x = info->player.pos.x;
	new_pos.y = info->player.pos.y;
	new_pos.x += cos(rotation_angle) * P_MOVE_SPEED;
	new_pos.y += sin(rotation_angle) * P_MOVE_SPEED;
	if (wall_collision(info->map, info->player.pos, new_pos))
	{
		info->player.pos.x = new_pos.x;
		info->player.pos.y = new_pos.y;
	}
}

void	set_newpos(t_global *pub)
{
	t_player	*player;
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
	t_global	*pub;

	(void)ypos;
	pub = (t_global *)param;
	pub->info->player.rotation_angle += to_rad(xpos - (WIDTH / 2)) * (double)0.100;
	mlx_set_mouse_pos(pub->mlx, (WIDTH / 2), (HEIGHT / 2));
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
		destroy_global(pub);
	handle_moves(player, keydata);
	handle_turn(player, keydata);
}
