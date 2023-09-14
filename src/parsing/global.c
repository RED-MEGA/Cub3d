/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:33:38 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/14 21:30:46 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_default_direction(t_info *info)
{
	if (info->player.direction == NO)
		info->player.rotation_angle = to_rad(90);
	else if (info->player.direction == SO)
		info->player.rotation_angle = to_rad(270);
	else if (info->player.direction == EA)
		info->player.rotation_angle = to_rad(0);
	else if (info->player.direction == WE)
		info->player.rotation_angle = to_rad(180);
}

t_global	*init_global(t_info *info)
{
	t_global	*global;

	global = (t_global *)malloc(sizeof(t_global));
	ft_error_ptr(global, 1);
	global->info = info;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	global->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!global->mlx)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	global->window_img = mlx_new_image(global->mlx, WIDTH, HEIGHT);
	if (!global->window_img)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	ft_error(mlx_image_to_window(global->mlx, global->window_img, 0, 0), 1);
	global->mode = MLX_MOUSE_HIDDEN;
	mlx_set_cursor_mode(global->mlx, MLX_MOUSE_HIDDEN);
	set_default_direction(info);
	load_texture(info);
	load_sprite_frames(info);
	return (global);
}
