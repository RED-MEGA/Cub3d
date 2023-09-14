/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_callback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:41:26 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/14 14:51:47 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_cursor(double xpos, double ypos, void *param)
{
	t_global	*pub;

	(void)ypos;
	pub = (t_global *)param;
	if (pub->mode == MLX_MOUSE_HIDDEN)
	{
		pub->info->player.rotation_angle += to_rad(xpos - (WIDTH / 2))
			* (double)0.100;
		mlx_set_mouse_pos(pub->mlx, (WIDTH / 2), (HEIGHT / 2));
	}
}

void	handle_mouse(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param)
{
	t_global	*pub;

	(void)mods;
	pub = (t_global *)param;
	if (mlx_is_mouse_down(pub->mlx, MLX_MOUSE_BUTTON_LEFT))
		pub->info->player.attack = true;
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		pub->info->player.attack = false;
	else if (mlx_is_mouse_down(pub->mlx, MLX_MOUSE_BUTTON_MIDDLE))
		open_door(pub);
	else if (mlx_is_mouse_down(pub->mlx, MLX_MOUSE_BUTTON_RIGHT))
		close_door(pub);
}
