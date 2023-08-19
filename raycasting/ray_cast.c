/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:27:06 by azarda            #+#    #+#             */
/*   Updated: 2023/08/19 05:07:30 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// float norm(float raymagic)
// {
// 	raymagic = remainder(raymagic, TWO_PI);
// 	if(raymagic < 0)
// 	{
// 		raymagic =  TWO_PI + raymagic;
// 	}
// 	return(raymagic);
// }

// void castoneray(float raymagic, int i)
// {
// 	raymagic = norm(raymagic);


// }

// void ray_cast(t_global *pub)
// {
// 	t_player player = pub->info->player;

// 	// printf("--> %p\n", player);
// 	double raymagic = player.rotation_angle - (FOV_ANGLE / 2);
// 	int i = 0;
// 	while (i < WIDTH)
// 	{
// 		castoneray(raymagic, i);
// 		raymagic += FOV_ANGLE / WIDTH;
// 		i++;
// 	}

// }


void ray_cast(t_global *pub)
{

	t_player player = pub->info->player;

	int new_x;
	int new_y;

	new_y = floor(player.pos.y / SQUARE_LEN) * SQUARE_LEN ;
	if(player.rotation_angle > PI &&  player.rotation_angle < 0)
		new_y += SQUARE_LEN;
	new_x = player.pos.x + (new_y - player.pos.y) / tan(player.rotation_angle);



	printf("==|%f|==\n",tan(player.rotation_angle));
	// exit(0);



	printf("-----ray cast -------\n");
}
