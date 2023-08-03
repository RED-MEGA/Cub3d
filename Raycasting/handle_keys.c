/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:08:10 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/03 22:05:51 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_keys(mlx_key_data_t keydata, t_global *pub)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(1);
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		pub->info->player.turn_d = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		pub->info->player.turn_d = -1;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		pub->info->player.turn_d = 1;
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		pub->info->player.turn_d = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		pub->info->player.turn_d = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		pub->info->player.turn_d = 0;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		pub->info->player.turn_d = 0;
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		pub->info->player.turn_d = 0;
	printf("%d\n", pub->info->player.turn_d);
}
