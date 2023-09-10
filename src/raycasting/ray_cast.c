/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:27:06 by azarda            #+#    #+#             */
/*   Updated: 2023/09/10 16:59:34 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_derec	ft_derection(double angle)
{
	t_derec	de;

	de.down = 0;
	de.up = 0;
	de.right = 0;
	de.left = 0;
	if (angle > 0 && angle < M_PI)
		de.down = 1;
	de.up = !de.down;
	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
		de.right = 1;
	de.left = !de.right;
	return (de);
}

void	flag_dor(t_pos diste, int *dor, int h, int v)
{
	if (diste.x < diste.y)
		*dor = h;
	else
		*dor = v;
}

t_pos	return_pos_ray(t_doubl ra, t_pos des, int *flag)
{
	t_pos	end_pos;

	if (des.x < des.y)
	{
		*flag = 1;
		end_pos.x = ra.a.x;
		end_pos.y = ra.a.y;
	}
	else
	{
		*flag = 2;
		end_pos.x = ra.b.x;
		end_pos.y = ra.b.y;
	}
	return (end_pos);
}

t_pos	ray_cast(t_global *pub, int *flag, int *dor)
{
	t_pos		horiso;
	t_pos		verti;
	t_pos		dest;
	int			h;
	int			v;

	pub->de = ft_derection(pub->info->player.ray_angle);
	dest.x = LONG_MAX;
	dest.y = LONG_MAX;
	horiso = ft_horizontal_inter(pub, pub->info->player, dor);
	if (horiso.x != -50 && horiso.y != -50)
		dest.x = calcul_distance(pub->info->player.pos, \
		(t_pos){.x = horiso.x, .y = horiso.y});
	h = *dor;
	*dor = 0;
	verti = ft_vertical_inter(pub, pub->info->player, dor);
	if (verti.x != -50 && verti.y != -50)
		dest.y = calcul_distance(pub->info->player.pos, \
		(t_pos){.x = verti.x, .y = verti.y});
	v = *dor;
	flag_dor((t_pos){.x = dest.x, .y = dest.y}, dor, h, v);
	return (return_pos_ray((t_doubl){.a = horiso, .b = verti},
		(t_pos){.x = dest.x, .y = dest.y}, flag));
}
