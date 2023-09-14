/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:39:14 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/14 14:51:47 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	close_door(t_global *pub)
{
	int	i;
	int	j;

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

void	open_door(t_global	*pub)
{
	int	i;
	int	j;

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
