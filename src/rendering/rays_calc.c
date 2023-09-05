/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:28:09 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/06 00:00:29 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_rays(t_global *pub)
{
	t_player	*player;

	player = &(pub->info->player);
	player->ray_angle = normalize_angle(player->rotation_angle - (FOV_ANGLE / 2));
	for (size_t i = 0; i < WIDTH; i++)
	{
		player->ray[i].dor = 0;
		player->ray[i].pos = ray_cast(pub, &(player->ray[i].flag), &(player->ray[i].dor));
		player->ray[i].angle = player->ray_angle;
		player->ray[i].len = calcul_distance(player->pos, player->ray[i].pos);
		// increment 
		player->ray_angle = normalize_angle(player->ray_angle + RAY_D);
	}
}
