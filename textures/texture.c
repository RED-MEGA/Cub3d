/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:33:44 by azarda            #+#    #+#             */
/*   Updated: 2023/09/02 21:18:27 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


unsigned int *ft_get_pixel_from_img(char *textur)
{
	t_pixel *ptr;

	ptr = malloc (sizeof(t_pixel));
	mlx_texture_t *img = mlx_load_png(textur);
	ptr->heith =  img->height;
	ptr->whidet = img->width;
	printf("hiet -> %d\n", img->height);
	printf("widt -> %d\n", img->width);
	// exit(0);
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


