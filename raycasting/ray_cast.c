/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:27:06 by azarda            #+#    #+#             */
/*   Updated: 2023/08/26 17:23:32 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize_angle(double angle)
{
	angle = remainder(angle, (M_PI * 2));
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle);
}

t_pos ray_cast(t_global *pub)
{
	t_player player = pub->info->player;


	double wallhit_x = 0; // whai
	double wallhit_y  = 0; // whai
	double distance = 0; //whai


	//----------------------------------------------------get view player -----------------------------------------

	int is_down = 0;
	int is_up = 0;
	int is_right = 0;
	int is_left = 0;

    if (player.ray_angle > 0 && player.ray_angle < M_PI)
        is_down = 1;
    	is_up = !is_down;
    if (player.ray_angle < 0.5 * M_PI || player.ray_angle > 1.5 * M_PI)
        	is_right = 1;
    	is_left = !is_right;


	// player.ray_angle *= (M_PI / 180);
	//------------------------------------------------horisontal-------------------------------------------------

	double x_inter;
	double y_inter;

	double step_x;
	double step_y;

	y_inter = floor(player.pos.y / SQUARE_LEN) * SQUARE_LEN;
	if(is_down)
		y_inter += SQUARE_LEN;
	x_inter = player.pos.x + (y_inter - player.pos.y) / tan(player.ray_angle);

	step_y = SQUARE_LEN;
	if(is_up)
		step_y *= -1;
	step_x = SQUARE_LEN / tan(player.ray_angle);
	if(is_left && step_x > 0)
		step_x *= -1;
	if(is_right && step_x < 0)
		step_x *= -1;

	double next_horiso_x = x_inter;
	double next_horiso_y = y_inter;
	if(is_up)
		next_horiso_y--;

	int flag_horison = 0;
	int x;
	int y;
	while(1)
	{
		x = floor(next_horiso_x / SQUARE_LEN);
		y = floor(next_horiso_y / SQUARE_LEN);
		if(x >= pub->info->map_m_size.j || y >= pub->info->map_m_size.i || x < 0 || y < 0)
			break;
		else
		{
			if(pub->info->map[y][x] == '1')
			{
				flag_horison = 1;
				break;
			}
			next_horiso_x += step_x;
			next_horiso_y += step_y;
		}
	}

	//------------------------------------vertical--------------------------------------------------


	double verti_x_inter;
	double verti_y_inter;

	double verti_step_x;
	double verti_step_y;

	verti_x_inter = floor(player.pos.x / SQUARE_LEN) * SQUARE_LEN;
	if(is_right)
		verti_x_inter += SQUARE_LEN;


	verti_y_inter = player.pos.y + (verti_x_inter - player.pos.x) *  tan(player.ray_angle);

	verti_step_x = SQUARE_LEN;
	if(is_left)
		verti_step_x *= -1;




	verti_step_y = SQUARE_LEN * tan(player.ray_angle);
	if(is_up && verti_step_y > 0)
		verti_step_y *= -1;
	if(is_down  && verti_step_y < 0)
		verti_step_y *= -1;

	double next_verti_x = verti_x_inter;
	double next_verti_y = verti_y_inter;
	if(is_left)
		next_verti_x--;

	int flag_vertical = 0;
	x = 0;
	y = 0;
	while(1)
	{
		x = floor(next_verti_x / SQUARE_LEN);
		y = floor(next_verti_y / SQUARE_LEN);
		if(x >= pub->info->map_m_size.j || y >= pub->info->map_m_size.i || x < 0 || y < 0)
			break;
		else
		{

			if(pub->info->map[y][x] == '1')
			{
				flag_vertical = 1;
				break;
			}
			next_verti_x += verti_step_x;
			next_verti_y += verti_step_y;
		}
	}
// ---------------------------------------------------calcul dectence -------------------------------------------------------
	t_pos end_pos;

	double  horisontal_distance = ULLONG_MAX;
	double  vertical_distance = ULLONG_MAX;
	if(flag_horison)
	{
		horisontal_distance = calcul_distance(player.pos, (t_pos) {.x = next_horiso_x, .y = next_horiso_y});
	}
	if(flag_vertical)
	{
		vertical_distance = calcul_distance(player.pos, (t_pos) {.x = next_verti_x, .y = next_verti_y});
	}
	if(horisontal_distance < vertical_distance)
	{
		end_pos.x = next_horiso_x;

	}
	else
		end_pos.x = next_verti_x;
	if(horisontal_distance < vertical_distance)
		end_pos.y = next_horiso_y;
	else
		end_pos.y = next_verti_y;
	return (end_pos);
}
