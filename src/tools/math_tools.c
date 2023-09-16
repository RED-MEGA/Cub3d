/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:12:54 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/16 19:02:51 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

double	to_rad(double degree)
{
	return (degree * (M_PI / 180));
}

double	to_degree(double rad)
{
	return (rad * (180 / M_PI));
}

double	calcul_distance(t_pos start, t_pos end)
{
	return (
		sqrt(
			pow(end.x - start.x, 2)
			+ 
			pow(end.y - start.y, 2) 
		)
	);
}

double	normalize_angle(double angle)
{
	angle = remainder(angle, (M_PI * 2));
	if (angle < 0)
		angle = (M_PI * 2) + angle;
	return (angle);
}
