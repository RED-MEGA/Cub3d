/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/03 14:36:03 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(mlx_image_t *image, t_info *info)
{
	t_pos	pos;
	int		distance;

	pos.y = -1;
	pos.x = -1;
	while (++pos.y < info->map_size.y)
	{
		pos.x = -1;
		while (++pos.x < info->map_size.x)
		{
			distance = sqrt(pow(info->player.pos.x - pos.x, 2) + pow(info->player.pos.y - pos.y, 2));
			if (distance < 10)
				mlx_put_pixel(image
						, pos.x, pos.y
						, get_rgb(RED_R, RED_G, RED_B, 255));
		}
	}
}

void	cub3d(char *file_name)
{
	t_global	*pub;
	t_info		*info;

	info = parsing(file_name);
	pub = init_global(info);

	to_2D_map(pub);

	draw_player(pub->window_img, pub->info);

	mlx_key_hook(pub->mlx, handle_keys, pub);

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