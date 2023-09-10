/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/10 04:50:23 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_image(mlx_image_t *image, uint32_t x, uint32_t y, mlx_image_t *img)
{
	t_pos	pos;
	int		i;
	int		color;

	i = 0;
	pos.x = -1;
	pos.y = -1;
	while (++pos.y < img->height)
	{
		pos.x = -1;
		while (++pos.x < img->width)
		{
			color = get_rgb(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2], 255);
			mlx_put_pixel_p(image, pos.x, pos.y, color);
			i += 4;
		}
	}
}

void	animated_sprite(t_global *pub)
{
	static int i;

	draw_image(pub->window_img, 0, 0, pub->sprite[0]);
	draw_image(pub->window_img, 0, 0, pub->sprite[1]);
	draw_image(pub->window_img, 0, 0, pub->sprite[2]);
	draw_image(pub->window_img, 0, 0, pub->sprite[3]);
	if (i == 4)
		i = 0;
	i++;
}

void	refresh_frame(void *param)
{
	clock_t t = clock();
	// Debug
	t_global	*pub;

	pub = (t_global *)param;
	set_newpos(pub);

	// update frame
	render(pub);
	minimap(pub);
	// animated_sprite(pub);
	
	// mlx_image_to_window(pub->mlx, pub->weapon
	// 	, HEIGHT - pub->weapon->height
	// 	, (WIDTH / 2) - (pub->weapon->width / 2));

	mlx_image_to_window(pub->mlx, pub->weapon
		, (WIDTH / 2) - (pub->weapon->width / 2)
		, HEIGHT - pub->weapon->height);
	// Debug
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("--- FPS :%d\n", (int)(1 / time_taken));
}

// void leaks () {system("leaks cub3D | grep LEAK");};

void	cub3d(char *file_name)
{
	// atexit(leaks);
	t_global	*pub;
	t_info		*info;

	info = parsing(file_name);
	pub = init_global(info);


	mlx_texture_t *texture;

	texture = mlx_load_png("img/axe.png");
	// pub->weapon = mlx_texture_to_image(pub->mlx, texture);
	// mlx_resize_image(pub->weapon
	// 	, pub->weapon->width * 0.2
	// 	, pub->weapon->height * 0.2);

	pub->weapon = mlx_texture_to_image(pub->mlx, texture);
	mlx_resize_image(pub->weapon
		, pub->weapon->width * 0.26
		, pub->weapon->height * 0.26);
	
	texture = mlx_load_png("img/sprite/frame1.png");
	pub->sprite[0] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame2.png");
	pub->sprite[1] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame3.png");
	pub->sprite[2] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame4.png");
	pub->sprite[3] = mlx_texture_to_image(pub->mlx, texture);


	mlx_mouse_hook(pub->mlx, handle_mouse_hook, pub);
	mlx_key_hook(pub->mlx, handle_keys, pub);
	mlx_cursor_hook(pub->mlx, handle_mouse, pub);
	mlx_close_hook(pub->mlx, destroy_global, pub);
	mlx_loop_hook(pub->mlx, refresh_frame, pub);
	mlx_loop(pub->mlx);
	mlx_terminate(pub->mlx);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
