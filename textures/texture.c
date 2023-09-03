/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:33:44 by azarda            #+#    #+#             */
/*   Updated: 2023/09/03 03:15:34 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int *lode_img_from_png(char *textur, int *width, int *height)
{
	mlx_texture_t *img = mlx_load_png(textur);
	*height = img->height;
	*width =  img->width;
	unsigned int *list = malloc(sizeof(unsigned int) * img->width * img->height);
	int i = 0;
	int j = 0;
	while (j < img->width * img->height)
	{
		list[j++] = get_rgb(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2], 255);
		i += 4;
	}
	return(list);
}

void  lode_texture(t_pixel *ptr, t_info *info)
{

	int width;
	int height;

	ptr->SO.buffer_img = lode_img_from_png(info->SO,&width, &height);
	ptr->SO.heith = height;
	ptr->SO.whidet = width;
	ptr->NO.buffer_img = lode_img_from_png(info->NO, &width, &height);
	ptr->NO.heith = height;
	ptr->NO.whidet = width;

}

unsigned int *ft_get_pixel_from_img(char *textur)
{
	return(0);
}

