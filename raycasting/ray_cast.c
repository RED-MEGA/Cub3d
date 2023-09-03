/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:27:06 by azarda            #+#    #+#             */
/*   Updated: 2023/09/03 04:55:55 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_derec ft_derection(t_player player)
{
	t_derec de;
	de.down = 0;
	de.up = 0;
	de.right = 0;
	de.left = 0;

    if (player.ray_angle > 0 && player.ray_angle < M_PI)
        de.down = 1;
    	de.up = !de.down;
    if (player.ray_angle < 0.5 * M_PI || player.ray_angle > 1.5 * M_PI)
        	de.right = 1;
    	de.left = !de.right;
	return(de);
}

t_pos ft_loop_calcul(t_pos inter, t_pos step, t_global *pub, int *flag)
{
	int x;
	int y;
	while(1)
	{
		x = floor(inter.x / SQUARE_LEN);
		y = floor(inter.y / SQUARE_LEN);
		if(x >= pub->info->map_m_size.j || y >= pub->info->map_m_size.i || x < 0 || y < 0)
			break;
		else
		{
			if(pub->info->map[y][x] == '1')
			{
				if(pub->de.up)
					inter.y++;
				*flag = 1;
				break;
			}
			inter.x += step.x;
			inter.y += step.y;
		}
	}
	return((t_pos){.x = inter.x, .y = inter.y});
}

t_pos ft_horizontal_inter(t_global *pub, t_player player, int *flag)
{
	t_pos inter;
	t_pos step;
	inter.y = floor(player.pos.y / SQUARE_LEN) * SQUARE_LEN;
	if(pub->de.down)
		inter.y += SQUARE_LEN;
	inter.x = player.pos.x + (inter.y - player.pos.y) / tan(player.ray_angle);
	step.y = SQUARE_LEN;
	if(pub->de.up)
		step.y *= -1;
	step.x = SQUARE_LEN / tan(player.ray_angle);
	if(pub->de.left && step.x > 0)
		step.x *= -1;
	if(pub->de.right && step.x < 0)
		step.x *= -1;
	if(pub->de.up)
		inter.y--;
	return(ft_loop_calcul(inter, step, pub, flag));
}

// t_pos ft_vertical_inter(t_global *pub, t_player player, int *flag)
// {

// }

t_pos ray_cast(t_global *pub, int *flag)
{
	t_player player = pub->info->player;

	pub->de = ft_derection(player);

	*flag = 0;
	t_pos horiso = ft_horizontal_inter(pub, player, flag);
	// t_pos verti = ft_vertical_inter(pub, player,flag);
	// player.ray_angle *= (M_PI / 180);

	//------------------------------------vertical--------------------------------------------------


	double verti_x_inter;
	double verti_y_inter;

	double verti_step_x;
	double verti_step_y;

	verti_x_inter = floor(player.pos.x / SQUARE_LEN) * SQUARE_LEN;
	if(pub->de.right)
		verti_x_inter += SQUARE_LEN;


	verti_y_inter = player.pos.y + (verti_x_inter - player.pos.x) *  tan(player.ray_angle);

	verti_step_x = SQUARE_LEN;
	if(pub->de.left)
		verti_step_x *= -1;




	verti_step_y = SQUARE_LEN * tan(player.ray_angle);
	if(pub->de.up && verti_step_y > 0)
		verti_step_y *= -1;
	if(pub->de.down  && verti_step_y < 0)
		verti_step_y *= -1;

	double next_verti_x = verti_x_inter;
	double next_verti_y = verti_y_inter;
	if(pub->de.left)
		next_verti_x--;

	int flag_vertical = 0;
	int x = 0;
	int y = 0;
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
				if(pub->de.left)
					next_verti_x++;
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
	if((*flag) == 1)
	{
		horisontal_distance = calcul_distance(player.pos, (t_pos) {.x = horiso.x, .y = horiso.y});
	}
	if(flag_vertical)
	{
		vertical_distance = calcul_distance(player.pos, (t_pos) {.x = next_verti_x, .y = next_verti_y});
	}
	if(horisontal_distance < vertical_distance)
	{
		*flag = 1;
		end_pos.x = horiso.x;
		end_pos.y = horiso.y;
	}
	else
	{
		*flag = 2;
		end_pos.x = next_verti_x;
		end_pos.y = next_verti_y;
	}
	return (end_pos);
}
