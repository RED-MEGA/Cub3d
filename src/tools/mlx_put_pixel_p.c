/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_put_pixel_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:37:18 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/04 14:17:56 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	mlx_put_pixel_p(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (!image)
		return ;
	if (!(x >= 0 && x < WIDTH)
		|| !(y >= 0 && y < HEIGHT))
		return ;
	mlx_put_pixel(image, x, y, color);
}
