/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:33:44 by azarda            #+#    #+#             */
/*   Updated: 2023/08/31 23:06:43 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


unsigned int *ft_get_pixel_from_img()
{

	mlx_texture_t *img = mlx_load_png("0.png");
	unsigned int *list = malloc(sizeof(unsigned int) * img->width * img->height);
	int i = 0;
	while (i < img->width * img->height)
	{
		list[i] = get_rgb(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2], img->pixels[i + 3]);
		i += 4;
	}
	return(list);
}



unsigned int *ft_texture(t_global *pub)
{




	mlx_texture_t	*texture = mlx_load_png("images.png");
	if(!texture)
		exit(0);

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



