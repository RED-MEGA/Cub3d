/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/02 15:44:55 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	refresh_frame(void *param)
{
	clock_t t = clock();
	// Debug
	t_global	*pub;

	pub = (t_global *)param;
	set_newpos(pub);





	// update frame
	calcul_rays(pub);
	render(pub);
	minimap(pub);

	// Debug
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("--- FPS :%d\n", (int)(1 / time_taken));
}

void	cub3d(char *file_name)
{
	t_global	*pub;
	t_info		*info;
	// mlx_t		*mlx;

	info = parsing(file_name);
	pub = init_global(info);
	pub->img = malloc(sizeof(t_pixel));

	// printf("-->>  %p\n", pub->img->EA);
	// exit(0);
	pub->img->EA = ft_get_pixel_from_img(pub->info->EA);
	pub->img->WE = ft_get_pixel_from_img(pub->info->WE);
	//---------------------------------------------------------------------------

	// mlx = pub->mlx;
	mlx_key_hook(pub->mlx, handle_keys, pub);
	mlx_cursor_hook(pub->mlx, handle_mouse, &pub->info->player);
	mlx_close_hook(pub->mlx, destroy_global, pub);
	mlx_loop_hook(pub->mlx, refresh_frame, pub);
	mlx_loop(pub->mlx);
	mlx_terminate(pub->mlx);
	destroy_global(pub);
	// use this for mlx resources
	// mlx_delete_xpm42();
	// mlx_delete_image();
	// mlx_delete_texture();
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
