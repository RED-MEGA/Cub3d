/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:33:44 by azarda            #+#    #+#             */
/*   Updated: 2023/09/08 17:26:18 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture(t_img *image)
{
	unsigned int	*buff;
	mlx_texture_t	*img;
	int i;
	int j;

	img = mlx_load_png(image->path);
	if (!img)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	image->height = img->height;
	image->width = img->width;
	buff = (unsigned int *)malloc(img->width * img->height * sizeof(unsigned int));
	ft_error_ptr(buff, 1);
	i = 0;
	j = 0;
	while (j < img->width * img->height)
	{
		buff[j++] = get_rgb(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2], 255);
		i += 4;
	}
	image->buffer_img = buff;
}

void  load_texture(t_info *info)
{
	init_texture(&info->NO);
	init_texture(&info->SO);
	init_texture(&info->WE);
	init_texture(&info->EA);
	init_texture(&info->DOOR);
}
