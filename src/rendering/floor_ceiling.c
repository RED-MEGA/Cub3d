/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:09:18 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/28 17:14:08 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fc(mlx_image_t *image, t_color color, t_pos pos)
{
	mlx_put_pixel_p(image, pos.x, pos.y,
		get_rgb(color.r, color.g, color.b, 255));
}
