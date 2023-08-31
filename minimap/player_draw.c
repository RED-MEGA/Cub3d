/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:47:56 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/31 18:09:46 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(mlx_image_t *image, t_pos start, t_pos end)
{
	double distance = calcul_distance(start, end);
	if (distance > 30)
	{
		double dx = (end.x - start.x) / distance; 
		double dy = (end.y - start.y) / distance;
		
		end.x = start.x + 30 * dx;
		end.y = start.y + 30 * dy;
	}
	int dx = end.x - start.x;
    int dy = end.y - start.y;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    double Xinc = dx / (double)steps;
    double Yinc = dy / (double)steps;
 
    // Put pixel for each step
    double X = start.x;
    double Y = start.y;
    for (int i = 0; i <= steps; i++)
	{
		mlx_put_pixel_p(image
		, X, Y
		, get_rgb(RED_R, RED_G, RED_B, 255));


		
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
    }
}

void	draw_player(mlx_image_t *image)
{
	t_pos	pos;
	int		distance;

	pos.y = -1;
	pos.x = -1;
	while (++pos.y < MINIMAP_SIZE)
	{
		pos.x = -1;
		while (++pos.x < MINIMAP_SIZE)
		{
			distance = calcul_distance((t_pos){.x = MINIMAP_SIZE / 2, .y = MINIMAP_SIZE / 2}, pos);
			if (distance < P_RADIUS)
				mlx_put_pixel_p(image
						, pos.x, pos.y
						, get_rgb(RED_R, RED_G, RED_B, 255));
		}
	}
}
