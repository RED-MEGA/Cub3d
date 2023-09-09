/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:28:09 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/09 21:17:51 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_ray(t_global *pub, t_player *player)
{
	player->ray.dor = 0;
	player->ray.pos = ray_cast(pub, &(player->ray.flag), &(player->ray.dor));
	player->ray.angle = player->ray_angle;
	player->ray.len = calcul_distance(player->pos, player->ray.pos);
}

void	render(t_global *pub)
{
	t_player	*player;
	double		wp;
	int			i;

	i = -1;
	player = &(pub->info->player);
	player->ray_angle = normalize_angle(player->rotation_angle - (FOV_ANGLE / 2));
	while (++i < WIDTH)
	{
		calcul_ray(pub, player);
		wp = calcul_wp(player);
		to_3d_ray(pub, i, wp);
		player->ray_angle = normalize_angle(player->ray_angle + RAY_D);
		player->ray.dor = 0;
	}
}
