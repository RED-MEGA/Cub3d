/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:47:56 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/04 21:47:32 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Using Bresenham's line algorithm
	// t_pos	draw_p;
	// t_pos	distance;
	// t_pos	sign;
	// t_pos	step;
	// int		fraction;
	// int		max_nb;

	// distance.y = end.y - start.y;
	// distance.x = end.x - start.x;
	// sign.y = distance.y > 0 ? 1 : -1;
	// sign.x = distance.x > 0 ? 1 : -1;
	// distance.y = abs(distance.y);
	// distance.x = abs(distance.x);
	// if (distance.x > distance.y)
	// {
	// 	step.x = sign.x;
	// 	step.y = 0;
	// 	fraction = distance.y / distance.x;
	// }
	// else
	// {
	// 	step.x = 0;
	// 	step.y = sign.y;
	// 	fraction = distance.x / distance.y;
	// }
	
	// int i = -1;
	// draw_p.x = start.x;
	// draw_p.y = start.y;
	// max_nb = distance.x > distance.y ? distance.x : distance.y; 

	// while (++i <= max_nb + 1)
	// {
	// 	mlx_put_pixel(image, draw_p.x, draw_p.y
	// 			, get_rgb(RED_R, RED_G, RED_B, 255));
	// 	draw_p.x += step.x;
	// 	draw_p.y += step.y;
	// 	if (draw_p.x == end.x && draw_p.y == end.y)
	// 		break ;
	// 	else if (distance.x > distance.y
	// 		&& (i + 1) * fraction >= (draw_p.y + 1 - start.y) / distance.y)
	// 		draw_p.x += sign.x;
	// 	else if (distance.x <= distance.y
	// 		&& (i + 1) * fraction >= (draw_p.x + 1 - start.x) / distance.x)
	// 		draw_p.y += sign.y;
	// }

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
		mlx_put_pixel(image
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
				mlx_put_pixel(image
						, pos.x, pos.y
						, get_rgb(RED_R, RED_G, RED_B, 255));
		}
	}
}
