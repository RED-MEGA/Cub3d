/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:56:34 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/14 21:24:13 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	_set_pi(t_player *player, t_loc pos)
{
	player->pos.x = (pos.j * SQUARE_LEN) + (SQUARE_LEN / 2);
	player->pos.y = (pos.i * SQUARE_LEN) + (SQUARE_LEN / 2);
	if (player->key == 'N')
		player->direction = NO;
	else if (player->key == 'S')
		player->direction = SO;
	else if (player->key == 'W')
		player->direction = WE;
	else if (player->key == 'E')
		player->direction = EA;
}

void	init_player(t_info *info)
{
	t_loc	loc;

	loc.i = -1;
	loc.j = -1;
	while (info->map[++loc.i])
	{
		loc.j = -1;
		while (info->map[loc.i][++loc.j])
		{
			if (info->map[loc.i][loc.j] == 'P')
			{
				_set_pi(&info->player, loc);
				return ;
			}
		}
	}
}
