/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/07 13:13:56 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fc(t_global *pub)
{
	t_pos	pos;

	pos.y = -1;
	while (++pos.y < HEIGHT)
	{
		pos.x = -1;
		while (++pos.x < WIDTH)
		{
			if (pos.y >= 0 && pos.y <= HEIGHT / 2)
				mlx_put_pixel(
					pub->window_img,
					pos.x,
					pos.y,
					get_rgb(
						pub->info->C.r,
						pub->info->C.g,
						pub->info->C.b,
						255));

			if (pos.y >= HEIGHT / 2 && pos.y <= HEIGHT)
				mlx_put_pixel(
					pub->window_img,
					pos.x,
					pos.y,
					get_rgb(
						pub->info->F.r,
						pub->info->F.g,
						pub->info->F.b,
						255));
		}
	}
}

void	refresh_frame(void *param)
{
	clock_t t = clock();
	t_global	*pub;

	pub = (t_global *)param;
	set_newpos(pub);
	// update frame
	to_2D_map(pub);







	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("--- FPS :%d\n", (int)(1 / time_taken));
}

void	cub3d(char *file_name)
{
	t_global	*pub;
	t_info		*info;

	info = parsing(file_name);
	pub = init_global(info);
	draw_fc(pub);
	to_2D_map(pub);

	mlx_key_hook(pub->mlx, handle_keys, pub);
	
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





// Parsing debug
// int debug_fd = open("Debug.log", O_RDWR);
// dprintf(debug_fd, "/* **************** */\n");
// dprintf(debug_fd, "/*     PARSING      */\n");
// dprintf(debug_fd, "/* **************** */\n");
// dprintf(debug_fd, "\nAttribute : \n");
// dprintf(debug_fd, "NO : %s \n", info->NO);
// dprintf(debug_fd, "SO : %s \n", info->SO);
// dprintf(debug_fd, "WE : %s \n", info->WE);
// dprintf(debug_fd, "EA : %s \n", info->EA);
// dprintf(debug_fd, "F : (%d,%d,%d) \n", info->F.r, info->F.g, info->F.b);
// dprintf(debug_fd, "C : (%d,%d,%d) \n", info->C.r, info->C.g, info->C.b);
// dprintf(debug_fd, "\nMap :\n");
// for (size_t i = 0; info->map[i]; i++)
// 	dprintf(debug_fd, "%s:newline\n", info->map[i]);
// printf("%sSUCCESS\n", GREEN);