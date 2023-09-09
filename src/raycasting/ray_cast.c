/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:27:06 by azarda            #+#    #+#             */
/*   Updated: 2023/09/09 21:06:59 by azarda           ###   ########.fr       */
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

t_pos ft_loop_calcul(t_doub_pos pos,  t_global *pub, int flag, int *dor)
{
	int x;
	int y;
	while(1)
	{
		x = floor(pos.a.x / SQUARE_LEN);
		y = floor(pos.a.y / SQUARE_LEN);
		if(x >= pub->info->map_m_size.j || y >= pub->info->map_m_size.i || x < 0 || y < 0)
			break;
		else
		{
			if(pub->info->map[y][x] == '1' || pub->info->map[y][x] == 'D')
			{
				if(flag == 1)
					pos.a.y++;
				if(flag == 2)
					pos.a.x++;
				if(pub->info->map[y][x] == 'D')
					*dor = 1;
				return((t_pos){.x = pos.a.x, .y = pos.a.y});
			}
			pos.a.x += pos.b.x;
			pos.a.y += pos.b.y;
		}
	}
	return((t_pos){.x = -50 , .y = -50});
}

t_pos ft_horizontal_inter(t_global *pub, t_player player, int *dor)
{
	t_pos inter;
	t_pos step;
	int flag;

	flag = 0;
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
	{
		inter.y--;
		flag = 1;
	}
	return(ft_loop_calcul((t_doub_pos){.a = inter, .b = step}, pub, flag, dor));
}

t_pos ft_vertical_inter(t_global *pub, t_player player, int *dor)
{
	t_pos inter;
	t_pos step;
	int flag;

	flag = 0;
	inter.x = floor(player.pos.x / SQUARE_LEN) * SQUARE_LEN;
	if(pub->de.right)
		inter.x += SQUARE_LEN;
	inter.y = player.pos.y + (inter.x - player.pos.x) *  tan(player.ray_angle);
	step.x = SQUARE_LEN;
	if(pub->de.left)
		step.x *= -1;
	step.y = SQUARE_LEN * tan(player.ray_angle);
	if(pub->de.up && step.y > 0)
		step.y *= -1;
	if(pub->de.down  && step.y < 0)
		step.y *= -1;
	if(pub->de.left)
	{
		inter.x--;
		flag = 2;
	}
	return(ft_loop_calcul((t_doub_pos){.a = inter, .b = step}, pub, flag, dor));
}




t_pos ray_cast(t_global *pub, int *flag, int  *dor)
{
	t_player player = pub->info->player;
	pub->de = ft_derection(player);

	*flag = 0;
	int h;
	int v;


	int flag_hori = 0;
	int flag_verti = 0;
	t_pos horiso = ft_horizontal_inter(pub, player, dor);
	if(horiso.x != -50 && horiso.y != -50)
		flag_hori = 1;
	h = *dor;

	*dor = 0;
	t_pos verti = ft_vertical_inter(pub, player, dor);
	if(verti.x != -50 && verti.y != -50)
		flag_verti = 1;
	v = *dor;


// ---------------------------------------------------calcul dectence -------------------------------------------------------
	t_pos end_pos;

	double  horisontal_distance = ULLONG_MAX;
	double  vertical_distance = ULLONG_MAX;

	if(flag_hori)
	{
		horisontal_distance = calcul_distance(player.pos, (t_pos) {.x = horiso.x, .y = horiso.y});
	}
	if(flag_verti)
	{
		vertical_distance = calcul_distance(player.pos, (t_pos) {.x = verti.x, .y = verti.y});
	}
	if(horisontal_distance < vertical_distance)
	{
		*flag = 1;
		*dor = h;
		end_pos.x = horiso.x;
		end_pos.y = horiso.y;
	}
	else
	{
		*flag = 2;
		*dor = v;
		end_pos.x = verti.x;
		end_pos.y = verti.y;
	}
	return (end_pos);
}
