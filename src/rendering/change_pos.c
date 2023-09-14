/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:08:49 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/14 18:46:29 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_pos	generate_newpos(t_pos pos,
					double rotation_angle, double move_speed)
{
	pos.x += cos(rotation_angle) * move_speed;
	pos.y += sin(rotation_angle) * move_speed;
	return (pos);
}

static bool	wall_collision(char **map, t_pos *oldpos, t_pos *newpos)
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

static double	get_ms(bool sprint)
{
	if (sprint)
		return (P_MOVE_SPEED * 2);
	return (P_MOVE_SPEED);
}

static void	get_new_pos(t_info *info, double rotation_angle)
{
	t_pos	new_pos;
	double	move_speed;

	move_speed = get_ms(info->player.sprint);
	new_pos = generate_newpos(info->player.pos, rotation_angle, move_speed);
	if (wall_collision(info->map, &info->player.pos, &new_pos))
		info->player.pos = new_pos;
}

void	update_position(t_info *info, t_player *player)
{
	double		rotation_angle;

	if (player->turn_d != 0)
		player->rotation_angle = normalize_angle(player->rotation_angle
				+ (double)player->turn_d * P_ROTATION_SPEED);
	if (player->move_v != NONE)
	{
		rotation_angle = player->rotation_angle;
		if (player->move_v == UP)
			;
		else if (player->move_v == DOWN)
			rotation_angle += to_rad(180);
		get_new_pos(info, rotation_angle);
	}
	if (player->move_h != NONE)
	{
		rotation_angle = player->rotation_angle;
		if (player->move_h == RIGHT)
			rotation_angle += to_rad(90);
		else if (player->move_h == LEFT)
			rotation_angle -= to_rad(90);
		get_new_pos(info, rotation_angle);
	}
}
