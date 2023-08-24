/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:29:43 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/24 23:37:20 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calculate 3d len_projection
/*
note 1:
	len_projection = (
		Square len / $ray_l3abd
		 * 
		((Width / 2) / tan(FOV / 2)))

note 2:
	START POS FOR DRAW = (
		(HIGTH / 2) - ($len_projection / 2)
	)
*/
double	calcul_wp(t_player	*player)
{
	// note 1:
}

void	to_3d_ray(double wp)
{
	// note 2:
}

void	render(t_global *pub)
{
	double wp;

	for (size_t i = 0; i < WIDTH; i++)
	{
		wp = calcul_wp(&pub->info->player);
		to_3d_ray(wp);
	}
}
