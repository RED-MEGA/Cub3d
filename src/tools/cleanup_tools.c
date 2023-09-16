/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:06:39 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/16 21:27:19 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	destroy_info(t_info *info)
{
	int	i;

	free(info->no.path);
	free(info->so.path);
	free(info->we.path);
	free(info->ea.path);
	free(info->door.path);
	free(info->no.buffer_img);
	free(info->so.buffer_img);
	free(info->we.buffer_img);
	free(info->ea.buffer_img);
	free(info->door.buffer_img);
	ft_free(info->map);
	if (info->weapon[0])
		mlx_delete_texture(info->weapon[0]);
	if (info->weapon[1])
		mlx_delete_texture(info->weapon[1]);
	i = -1;
	while (++i < 10)
		if (info->sprite[i])
			mlx_delete_texture(info->sprite[i]);
	free(info);
}

void	destroy_global(void *param)
{
	t_global	*pub;

	pub = (t_global *)param;
	destroy_info(pub->info);
	mlx_delete_image(pub->mlx, pub->window_img);
	mlx_terminate(pub->mlx);
	free(pub);
	exit(0);
}
