/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/09 17:57:25 by reben-ha         ###   ########.fr       */
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
	render(pub);
	minimap(pub);

	// Debug
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("--- FPS :%d\n", (int)(1 / time_taken));
}

void	handle_mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		return (check_dor_open((t_global *)param));
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		return (check_dor_close((t_global *)param));
}

// void leaks () {system("leaks cub3D | grep LEAK");};

void	cub3d(char *file_name)
{
	// atexit(leaks);
	t_global	*pub;
	t_info		*info;

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

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
