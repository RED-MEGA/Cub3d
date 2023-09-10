/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:37:40 by azarda            #+#    #+#             */
/*   Updated: 2023/09/10 16:58:41 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pos	ft_cheak_flag(t_doubl pos, int flag)
{
	if (flag == 1)
		pos.a.y++;
	if (flag == 2)
		pos.a.x++;
	return ((t_pos){.x = pos.a.x, .y = pos.a.y});
}

t_pos	ft_loop_calcul(t_doubl pos, t_global *pub, int flag, int *dor)
{
	int	x;
	int	y;

	while (1)
	{
		x = floor(pos.a.x / SQUARE_LEN);
		y = floor(pos.a.y / SQUARE_LEN);
		if (x >= pub->info->map_m_size.j || \
				y >= pub->info->map_m_size.i || x < 0 || y < 0)
			break ;
		else
		{
			if (pub->info->map[y][x] == '1' || pub->info->map[y][x] == 'D')
			{
				if (pub->info->map[y][x] == 'D')
					*dor = 1;
				return (ft_cheak_flag(pos, flag));
			}
			pos.a.x += pos.b.x;
			pos.a.y += pos.b.y;
		}
	}
	return ((t_pos){.x = -50, .y = -50});
}

t_pos	ft_horizontal_inter(t_global *pub, t_player player, int *dor)
{
	t_pos	inter;
	t_pos	step;
	int		flag;

	flag = 0;
	inter.y = floor(player.pos.y / SQUARE_LEN) * SQUARE_LEN;
	if (pub->de.down)
		inter.y += SQUARE_LEN;
	inter.x = player.pos.x + (inter.y - player.pos.y) / tan(player.ray_angle);
	step.y = SQUARE_LEN;
	if (pub->de.up)
		step.y *= -1;
	step.x = SQUARE_LEN / tan(player.ray_angle);
	if (pub->de.left && step.x > 0)
		step.x *= -1;
	if (pub->de.right && step.x < 0)
		step.x *= -1;
	if (pub->de.up)
	{
		inter.y--;
		flag = 1;
	}
	return (ft_loop_calcul((t_doubl){.a = inter, .b = step}, pub, flag, dor));
}

t_pos	ft_vertical_inter(t_global *pub, t_player player, int *dor)
{
	t_pos	inter;
	t_pos	step;
	int		flag;

	flag = 0;
	inter.x = floor(player.pos.x / SQUARE_LEN) * SQUARE_LEN;
	if (pub->de.right)
		inter.x += SQUARE_LEN;
	inter.y = player.pos.y + (inter.x - player.pos.x) * tan(player.ray_angle);
	step.x = SQUARE_LEN;
	if (pub->de.left)
		step.x *= -1;
	step.y = SQUARE_LEN * tan(player.ray_angle);
	if (pub->de.up && step.y > 0)
		step.y *= -1;
	if (pub->de.down && step.y < 0)
		step.y *= -1;
	if (pub->de.left)
	{
		inter.x--;
		flag = 2;
	}
	return (ft_loop_calcul((t_doubl){.a = inter, .b = step}, pub, flag, dor));
}
