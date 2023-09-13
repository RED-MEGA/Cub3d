/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:06:39 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/13 17:41:53 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	destroy_info(t_info *info)
{
	int	i;

	free(info->NO.path);
	free(info->SO.path);
	free(info->WE.path);
	free(info->EA.path);
	free(info->DOOR.path);
	free(info->NO.buffer_img);
	free(info->SO.buffer_img);
	free(info->WE.buffer_img);
	free(info->EA.buffer_img);
	free(info->DOOR.buffer_img);
	ft_free(info->map);
	mlx_delete_texture(info->weapon[0]);
	mlx_delete_texture(info->weapon[1]);
	i = -1;
	while (++i < 10)
		mlx_delete_texture(info->sprite[i]);
	free(info);
}

void	destroy_global(void *param)
{
	t_global *pub;

	pub = (t_global *)param;
	destroy_info(pub->info);
	mlx_delete_image(pub->mlx, pub->window_img);
	mlx_terminate(pub->mlx);
	free(pub);
	exit(0);
}
