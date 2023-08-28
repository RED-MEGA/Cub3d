/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/28 14:41:40 by reben-ha         ###   ########.fr       */
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

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_global	*pub;
	t_player	*player;

	pub = (t_global *)param;
	player = &(pub->info->player);
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);

	// Handle (UP, DOWN)
	if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->move_v = UP;
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->move_v = DOWN;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		player->move_v = NONE;
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		player->move_v = NONE;

	// Handle (RIGHT, LEFT)
	if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->move_h = RIGHT;
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		player->move_h = LEFT;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		player->move_h = NONE;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		player->move_h = NONE;

	// Handle turn
	if (keydata.key == MLX_KEY_RIGHT
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
