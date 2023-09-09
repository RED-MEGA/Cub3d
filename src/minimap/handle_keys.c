/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/09 16:23:23 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	wall_collision(char **map, t_pos oldpos, t_pos newpos)
{
	if (map[(int)(newpos.y / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != '1'
		&& map[(int)((newpos.y + (P_RADIUS * 0.4)) / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != '1'
		&& map[(int)((newpos.y - (P_RADIUS * 0.4)) / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != '1'
		&& map[(int)(newpos.y / SQUARE_LEN)][(int)((newpos.x + (P_RADIUS * 0.4)) / SQUARE_LEN)] != '1'
		&& map[(int)(newpos.y / SQUARE_LEN)][(int)((newpos.x - (P_RADIUS * 0.4)) / SQUARE_LEN)] != '1'
		&& map[(int)(oldpos.y / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != '1'
		&& map[(int)(newpos.y / SQUARE_LEN)][(int)(oldpos.x / SQUARE_LEN)] != '1'




		&& map[(int)(newpos.y / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != 'D'
		&& map[(int)((newpos.y + (P_RADIUS * 0.4)) / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != 'D'
		&& map[(int)((newpos.y - (P_RADIUS * 0.4)) / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != 'D'
		&& map[(int)(newpos.y / SQUARE_LEN)][(int)((newpos.x + (P_RADIUS * 0.4)) / SQUARE_LEN)] != 'D'
		&& map[(int)(newpos.y / SQUARE_LEN)][(int)((newpos.x - (P_RADIUS * 0.4)) / SQUARE_LEN)] != 'D'
		&& map[(int)(oldpos.y / SQUARE_LEN)][(int)(newpos.x / SQUARE_LEN)] != 'D'
		&& map[(int)(newpos.y / SQUARE_LEN)][(int)(oldpos.x / SQUARE_LEN)] != 'D')
		return (true);
	return (false);
}

double	get_ms(bool sprint)
{
	if (sprint)
		return (P_MOVE_SPEED * 2);
	return (P_MOVE_SPEED);
}

void	get_new_pos(t_info *info, double rotation_angle)
{
	t_pos	new_pos;

	new_pos.x = info->player.pos.x;
	new_pos.y = info->player.pos.y;
	new_pos.x += cos(rotation_angle) * get_ms(info->player.sprint);
	new_pos.y += sin(rotation_angle) * get_ms(info->player.sprint);
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
}

void	handle_mouse(double xpos, double ypos, void* param)
{
	t_global	*pub;

	(void)ypos;
	pub = (t_global *)param;
	if (pub->mode == MLX_MOUSE_HIDDEN)
	{
		pub->info->player.rotation_angle += to_rad(xpos - (WIDTH / 2)) * (double)0.100;
		mlx_set_mouse_pos(pub->mlx, (WIDTH / 2), (HEIGHT / 2));
	}
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

void	check_dor_close(t_global	*pub)
{
	int i,j;

	i = (int)(pub->info->player.pos.x / SQUARE_LEN);
	j = (int)(pub->info->player.pos.y / SQUARE_LEN);
	if (pub->info->map[j][i + 1] == 'd')
		pub->info->map[j][i + 1] = 'D';
	else if (pub->info->map[j][i - 1] == 'd')
		pub->info->map[j][i - 1] = 'D';
	else if (pub->info->map[j + 1][i] == 'd')
		pub->info->map[j + 1][i] = 'D';
	else if (pub->info->map[j - 1][i] == 'd')
		pub->info->map[j - 1][i] = 'D';
}

void	check_dor_open(t_global	*pub)
{
	int i,j;

	i = (int)(pub->info->player.pos.x / SQUARE_LEN);
	j = (int)(pub->info->player.pos.y / SQUARE_LEN);
	if (pub->info->map[j][i + 1] == 'D')
		pub->info->map[j][i + 1] = 'd';
	else if (pub->info->map[j][i - 1] == 'D')
		pub->info->map[j][i - 1] = 'd';
	else if (pub->info->map[j + 1][i] == 'D')
		pub->info->map[j + 1][i] = 'd';
	else if (pub->info->map[j - 1][i] == 'D')
		pub->info->map[j - 1][i] = 'd';
}

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_global	*pub;

	pub = (t_global *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		destroy_global(pub);
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
		return (check_dor_open(pub));
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		return (check_dor_close(pub));
	if (keydata.key == MLX_KEY_LEFT_SHIFT)
	{
		if (key_press(keydata, MLX_KEY_LEFT_SHIFT))
			pub->info->player.sprint = true;
		else if (key_release(keydata, MLX_KEY_LEFT_SHIFT))
			pub->info->player.sprint = false;
		return ;
	}
	if (key_press(keydata, MLX_KEY_F))
	{
		if (pub->mode == MLX_MOUSE_HIDDEN)
			pub->mode = MLX_MOUSE_NORMAL;
		else
			pub->mode = MLX_MOUSE_HIDDEN;
		mlx_set_cursor_mode(pub->mlx, pub->mode);
		return ;
	}
	handle_moves(&pub->info->player, keydata);
	handle_turn(&pub->info->player, keydata);
}
