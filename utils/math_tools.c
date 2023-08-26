/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:12:54 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/26 17:24:47 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

//1° × π/180 = 0.01745rad
double	to_rad(double degree)
{
	return (degree * (PI / 180));
}

// 1rad × 180/π = 57.296°
double	to_degree(double rad)
{
	return (rad * (180 / PI));
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
