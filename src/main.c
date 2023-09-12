/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
// /*   Updated: 2023/09/11 19:08:18 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_image(mlx_image_t *image, int x, int y, mlx_texture_t *texture)
{
	int	x_tmp;
	int	y_tmp;
	int	i;
	int	color;

	i = 0;
	x_tmp = x;
	y_tmp = y;
	while (y < (y_tmp + texture->height))
	{
		x = x_tmp;
		while (x < (x_tmp + texture->width))
		{
			color = get_rgb(texture->pixels[i], texture->pixels[i + 1], texture->pixels[i + 2], 255);
			if (color != 255)
				mlx_put_pixel_p(image, x, y, color);
			i += texture->bytes_per_pixel;
			x++;
		}
		y++;
	}
}

void animated_sprite(t_global *pub)
{
	t_info					*info;
	int						x;
	int						y;
	static unsigned char	i;
	unsigned char	repeat = 3;


	info = (t_info *)pub->info;
	x = (WIDTH / 2) - (info->sprite[0]->width / 2);
	y = 0;
	if ((i / repeat) == 0)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 1)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 2)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 3)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 4)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 5)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 6)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 7)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 8)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	else if ((i / repeat) == 9)
		draw_image(pub->window_img, x, y, info->sprite[(i / repeat)]);
	i++;
	if (i >= (9 * repeat))
		i = 0;
}

void	mjollnir(t_global *pub)
{
	int y;
	int x;
	int	frame_i;

	frame_i = 0;
	if (pub->info->player.attack == true)
	{
		animated_sprite(pub);
		frame_i = 1;
	}
	x = (WIDTH / 2) - (pub->info->weapon[frame_i]->width / 2);
	y = HEIGHT - pub->info->weapon[frame_i]->height;
	draw_image(pub->window_img, x, y, pub->info->weapon[frame_i]);
}

void	refresh_frame(void *param)
{
	clock_t t = clock();
	// Debug
	t_global *pub;

	pub = (t_global *)param;
	set_newpos(pub);
	// update frame
	render(pub);
	minimap(pub);
	mjollnir(pub);
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
