/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 02:06:39 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/04 14:17:56 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	destroy_info(t_info *info)
{
	free(info->NO);
	free(info->SO);
	free(info->WE);
	free(info->EA);
	ft_free(info->map);
	free(info);
}

void	destroy_global(void *param)
{
	t_global *pub;

	pub = (t_global *)param;
	destroy_info(pub->info);
	free(pub);
	exit(0);
}
	// use this for mlx resources
	// mlx_delete_xpm42();
	// mlx_delete_image();
	// mlx_delete_texture();  