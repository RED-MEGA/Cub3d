/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:33:44 by azarda            #+#    #+#             */
/*   Updated: 2023/09/02 12:58:22 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


unsigned int *ft_get_pixel_from_img(char *textur)
{
	t_pixel *ptr;

	ptr = malloc (sizeof(t_pixel));
	mlx_texture_t *img = mlx_load_png("STARG2_64.png");
	ptr->heith =  img->height;
	ptr->whidet = img->width;
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



int ft_texture(t_global *pub, int start, int end, double wp, int number_rey)
{







	// while(pub->img->EA[i])
	// {
	// 	printf(" -> %x\n", pub->img->EA[i]);
	// 	i++;
	// }
	// exit(0);

	// return(tess);


	// uint32_t color_text = pub->img->EA[(pub->img->img->width * ofset_y) + ofset_x];

	// pub->img->EA[(WIDTH * i) + number_rey];

	// Convert texture to a displayable image
	// mlx_image_t* img = mlx_texture_to_image(pub->mlx, texture);


	// Display the image
	// mlx_image_to_window(pub->mlx, img, 0, 0);


	// printf("xxx  %d\n", ptr->bytes_per_pixel);
	// printf("color  %d\n", );
	// printf("color = %d %d %d %d\n", ptr->pixels[0], ptr->pixels[1], ptr->pixels[2], ptr->pixels[3]);



	// exit(0);

	// ptr->bytes_per_pixel;
	// mlx_put_pixel_p(pub->window_img, ptr->height, ptr->width,ptr->bytes_per_pixel);

}



