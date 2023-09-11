/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/11 19:08:18 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_image(mlx_image_t *image, int x, int y, mlx_image_t *img)
{
	int	x_tmp;
	int	y_tmp;
	int	i;
	int	color;

	i = 0;
	x_tmp = x;
	y_tmp = y;
	while (y < (y_tmp + img->height))
	{
		x = x_tmp;
		while (x < (x_tmp + img->width))
		{
			color = get_rgb(img->pixels[i], img->pixels[i + 1], img->pixels[i + 2], 255);
			if (color != 0xff)
				mlx_put_pixel_p(image, x, y, color);
			i += 4;
			x++;
		}
		y++;
	}
}

void animated_sprite(t_global *pub)
{
	static unsigned char i;
	int x = (WIDTH / 2) - (pub->sprite[0]->width / 2);
	int y = (HEIGHT / 2) - (pub->sprite[0]->height / 2);

	if (i == 0)
	{
		draw_image(pub->window_img, x, y, pub->sprite[0]);
		printf("pub->sprite\n");
	}
	else if (i == 1)
	{
		draw_image(pub->window_img, x, y, pub->sprite[1]);
		printf("pub->sprite\n");
	}
	else if (i == 2)
	{
		draw_image(pub->window_img, x, y, pub->sprite[2]);
		printf("pub->sprite\n");
	}
	else if (i == 3)
	{
		draw_image(pub->window_img, x, y, pub->sprite[3]);
		printf("pub->sprite\n");
	}
	else if (i == 4)
	{
		draw_image(pub->window_img, x, y, pub->sprite[4]);
		printf("pub->sprite\n");
	}
	else if (i == 5)
	{
		draw_image(pub->window_img, x, y, pub->sprite[5]);
		printf("pub->sprite\n");
	}
	else if (i == 6)
	{
		draw_image(pub->window_img, x, y, pub->sprite[6]);
		printf("pub->sprite\n");
	}
	else if (i == 7)
	{
		draw_image(pub->window_img, x, y, pub->sprite[7]);
		printf("pub->sprite\n");
	}
	else if (i == 8)
	{
		draw_image(pub->window_img, x, y, pub->sprite[8]);
		printf("pub->sprite\n");
	}
	else if (i == 9)
	{
		draw_image(pub->window_img, x, y, pub->sprite[9]);
		printf("pub->sprite\n");
	}
	else if (i == 10)
	{
		draw_image(pub->window_img, x, y, pub->sprite[10]);
		printf("pub->sprite\n");
	}
	else if (i == 11)
	{
		draw_image(pub->window_img, x, y, pub->sprite[11]);
		printf("pub->sprite\n");
	}
	else if (i == 12)
	{
		draw_image(pub->window_img, x, y, pub->sprite[12]);
		printf("pub->sprite\n");
	}
	else if (i == 13)
	{
		draw_image(pub->window_img, x, y, pub->sprite[13]);
		printf("pub->sprite\n");
	}
	i++;
	if (i == 14)
		i = 0;
}

void refresh_frame(void *param)
{
	clock_t t = clock();
	// Debug
	t_global *pub;

	pub = (t_global *)param;
	set_newpos(pub);

	// update frame
	render(pub);
	minimap(pub);
	draw_image(pub->window_img, 0, 0, pub->weapon);

	// mlx_image_to_window(pub->mlx, pub->weapon
	// 	, HEIGHT - pub->weapon->height
	// 	, (WIDTH / 2) - (pub->weapon->width / 2));

	animated_sprite(pub);
	// Debug
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("--- FPS :%d\n", (int)(1 / time_taken));
}

// void leaks () {system("leaks cub3D | grep LEAK");};

void cub3d(char *file_name)
{
	// atexit(leaks);
	t_global *pub;
	t_info *info;

	info = parsing(file_name);
	pub = init_global(info);

	mlx_texture_t *texture;

	texture = mlx_load_png("img/Mjollnir.png");
	pub->weapon = mlx_texture_to_image(pub->mlx, texture);
	mlx_resize_image(pub->weapon, pub->weapon->width * 0.2, pub->weapon->height * 0.2);

	// pub->weapon = mlx_texture_to_image(pub->mlx, texture);
	// mlx_resize_image(pub->weapon
	// 	, pub->weapon->width * 0.26
	// 	, pub->weapon->height * 0.26);
	// mlx_image_to_window(pub->mlx, pub->weapon
	// 	, (WIDTH / 2) - (pub->weapon->width / 2)
	// 	, HEIGHT - pub->weapon->height);

	texture = mlx_load_png("img/sprite/frame_00.png");
	pub->sprite[0] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_01.png");
	pub->sprite[1] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_02.png");
	pub->sprite[2] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_03.png");
	pub->sprite[3] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_04.png");
	pub->sprite[4] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_05.png");
	pub->sprite[5] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_06.png");
	pub->sprite[6] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_07.png");
	pub->sprite[7] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_08.png");
	pub->sprite[8] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_09.png");
	pub->sprite[9] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_10.png");
	pub->sprite[10] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_11.png");
	pub->sprite[11] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_12.png");
	pub->sprite[12] = mlx_texture_to_image(pub->mlx, texture);
	texture = mlx_load_png("img/sprite/frame_13.png");
	pub->sprite[13] = mlx_texture_to_image(pub->mlx, texture);

	mlx_mouse_hook(pub->mlx, handle_mouse_hook, pub);
	mlx_key_hook(pub->mlx, handle_keys, pub);
	mlx_cursor_hook(pub->mlx, handle_mouse, pub);
	mlx_close_hook(pub->mlx, destroy_global, pub);
	mlx_loop_hook(pub->mlx, refresh_frame, pub);
	mlx_loop(pub->mlx);
	mlx_terminate(pub->mlx);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
