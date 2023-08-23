/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:47:56 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/23 18:45:50 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(mlx_image_t *image, t_pos start, t_pos end)
{
	int dx = end.x - start.x;
    int dy = end.y - start.y;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = start.x;
    float Y = start.y;
    for (int i = 0; i <= steps; i++)
	{
		mlx_put_pixel_p(image
		, X, Y
		, get_rgb(RED_R, RED_G, RED_B, 255));


		
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
    }
}

void	draw_player(mlx_image_t *image, t_info *info)
{
	t_pos	pos;
	int		distance;

	pos.y = -1;
	pos.x = -1;
	while (++pos.y < info->map_size.y)
	{
		pos.x = -1;
		while (++pos.x < info->map_size.x)
		{
			distance = sqrt(pow(info->player.pos.x - pos.x, 2)
					 + pow(info->player.pos.y - pos.y, 2));
			if (distance < P_RADIUS)
				mlx_put_pixel_p(image
						, pos.x, pos.y
						, get_rgb(RED_R, RED_G, RED_B, 255));
		}
	}
}
