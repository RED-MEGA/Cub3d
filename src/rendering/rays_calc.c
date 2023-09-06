/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:28:09 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/06 00:51:45 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_rays(t_global *pub)
{
	t_player	*player;
	double	wp;

	player = &(pub->info->player);
	player->ray_angle = normalize_angle(player->rotation_angle - (FOV_ANGLE / 2));
	for (size_t i = 0; i < WIDTH; i++)
	{
		player->ray.dor = 0;
		player->ray.pos = ray_cast(pub, &(player->ray.flag), &(player->ray.dor));
		player->ray.angle = player->ray_angle;
		player->ray.len = calcul_distance(player->pos, player->ray.pos);
		// increment 
		wp = calcul_wp(player, i);
		to_3d_ray(pub, i, wp);
		player->ray_angle = normalize_angle(player->ray_angle + RAY_D);
		player->ray.dor = 0;
	}
}
