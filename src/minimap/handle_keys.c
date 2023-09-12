/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/12 22:45:42 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	pos_to_char(char **map, double y, double x)
{
	return (map[(int)(y / SQUARE_LEN)][(int)(x / SQUARE_LEN)]);
}

t_pos	generate_newpos(t_pos pos, double rotation_angle, double move_speed)
{
	pos.x += cos(rotation_angle) * move_speed;
	pos.y += sin(rotation_angle) * move_speed;
	return (pos);
}

bool	select_range(t_info *info, double move_speed, double *range_s, double *range_e)
{
	t_pos	new_pos;
	double	sliding_angle;
	char	char_pos;

	sliding_angle = normalize_angle(info->player.rotation_angle - to_rad(30));
	new_pos = generate_newpos(info->player.pos, sliding_angle, move_speed);
	char_pos = pos_to_char(info->map, new_pos.y, new_pos.x);
	if (char_pos == '0' || char_pos == 'd')
	{
		*range_s = to_degree(sliding_angle);
		*range_e = to_degree(normalize_angle(sliding_angle + to_rad(20)));
		return (true);
	}
	sliding_angle = normalize_angle(info->player.rotation_angle + to_rad(30));
	new_pos = generate_newpos(info->player.pos, sliding_angle, move_speed);
	char_pos = pos_to_char(info->map, new_pos.y, new_pos.x);
	if (char_pos == '0' || char_pos == 'd')
	{
		*range_s = to_degree(normalize_angle(sliding_angle - to_rad(20)));
		*range_e = to_degree(sliding_angle);
		return (true);
	}
	return (false);
}

bool	try_sliding(t_info *info, double move_speed, t_pos *new_pos)
{
	// check which range you need to check (-30 to 0, or 0 to +30)
	double	range_s;
	double	range_e;

	if (!select_range(info, move_speed, &range_s, &range_e))
		return (false);
	printf("Range is %f -> %f\n", range_s ,range_e);
	// in Loop increment the value of rotation angle to find sliding_pos
	double	sliding_angle;
	char	char_pos;

	sliding_angle = range_s;
	while (sliding_angle <= range_e)
	{
		*new_pos = generate_newpos(info->player.pos, to_rad(sliding_angle), move_speed);
		if (wall_collision(info->map, &info->player.pos, new_pos))
			return (true);
		sliding_angle++;
	}
	return (false);	
}

bool	wall_collision(char **map, t_pos *oldpos, t_pos *newpos)
{
	if (pos_to_char(map, newpos->y, newpos->x) != '1'
		&& pos_to_char(map, newpos->y + (P_RADIUS * 0.4), newpos->x) != '1'
		&& pos_to_char(map, newpos->y - (P_RADIUS * 0.4), newpos->x) != '1'
		&& pos_to_char(map, newpos->y, newpos->x + (P_RADIUS * 0.4)) != '1'
		&& pos_to_char(map, newpos->y, newpos->x - (P_RADIUS * 0.4)) != '1'
		&& pos_to_char(map, oldpos->y, newpos->x) != '1'
		&& pos_to_char(map, newpos->y, oldpos->x) != '1'

		&& pos_to_char(map, newpos->y, newpos->x) != 'D'
		&& pos_to_char(map, newpos->y + (P_RADIUS * 0.4), newpos->x) != 'D'
		&& pos_to_char(map, newpos->y - (P_RADIUS * 0.4), newpos->x) != 'D'
		&& pos_to_char(map, newpos->y, newpos->x + (P_RADIUS * 0.4)) != 'D'
		&& pos_to_char(map, newpos->y, newpos->x - (P_RADIUS * 0.4)) != 'D'
		&& pos_to_char(map, oldpos->y, newpos->x) != 'D'
		&& pos_to_char(map, newpos->y, oldpos->x) != 'D')
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
	double	move_speed;

	move_speed = get_ms(info->player.sprint);
	new_pos = generate_newpos(info->player.pos, rotation_angle, move_speed);
	if (wall_collision(info->map, &info->player.pos, &new_pos))
		info->player.pos = new_pos;
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

void	handle_mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_global	*pub;

	(void)mods;
	pub = (t_global *)param;
	if (mlx_is_mouse_down(pub->mlx, MLX_MOUSE_BUTTON_LEFT))
		pub->info->player.attack = true;
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		pub->info->player.attack = false;
	else if (mlx_is_mouse_down(pub->mlx, MLX_MOUSE_BUTTON_MIDDLE))
		check_dor_open(pub);
	else if (mlx_is_mouse_down(pub->mlx, MLX_MOUSE_BUTTON_RIGHT))
		check_dor_close(pub);
}
