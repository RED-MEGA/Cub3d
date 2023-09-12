/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:04:16 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/12 16:04:39 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*load_frame(mlx_t *mlx, char *path)
{
	mlx_texture_t	*texture;
	
	texture = mlx_load_png(path);
	if (!texture)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	// mlx_resize_image(pub->sprite[0], pub->sprite[0]->height * 0.5, pub->sprite[0]->width * 0.5);
	return (texture);
}

void	load_sprite_frames(t_info *info, mlx_t *mlx)
{
	info->weapon[0] = load_frame(mlx, "img/Mjollnir_in_attack.png");
	info->weapon[1] = load_frame(mlx, "img/Mjollnir_in_normal.png");

	info->sprite[0] = load_frame(mlx, "img/Sprite_frames_t/frame_00.png");
	info->sprite[1] = load_frame(mlx, "img/Sprite_frames_t/frame_01.png");
	info->sprite[2] = load_frame(mlx, "img/Sprite_frames_t/frame_02.png");
	info->sprite[3] = load_frame(mlx, "img/Sprite_frames_t/frame_03.png");
	info->sprite[4] = load_frame(mlx, "img/Sprite_frames_t/frame_04.png");
	info->sprite[5] = load_frame(mlx, "img/Sprite_frames_t/frame_05.png");
	info->sprite[6] = load_frame(mlx, "img/Sprite_frames_t/frame_06.png");
	info->sprite[7] = load_frame(mlx, "img/Sprite_frames_t/frame_07.png");
	info->sprite[8] = load_frame(mlx, "img/Sprite_frames_t/frame_08.png");
	info->sprite[9] = load_frame(mlx, "img/Sprite_frames_t/frame_09.png");
}

void	get_derection_engel(t_info *inf)
{
	if (inf->player.direction == NO)
		inf->player.rotation_angle = to_rad(90);
	else if (inf->player.direction == SO)
		inf->player.rotation_angle = to_rad(270);
	else if (inf->player.direction == EA)
		inf->player.rotation_angle = to_rad(0);
	else if (inf->player.direction == WE)
		inf->player.rotation_angle = to_rad(180);
}

t_global	*init_global(t_info *info)
{
	t_global	*global;

	global = (t_global *)malloc(sizeof(t_global));
	ft_error_ptr(global, 1);
	global->info = info;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1); // Note
	global->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!global->mlx)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	global->window_img = mlx_new_image(global->mlx, WIDTH, HEIGHT);
	if (!global->window_img)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	ft_error(mlx_image_to_window(global->mlx, global->window_img, 0, 0), 1);
	global->mode = MLX_MOUSE_HIDDEN;
	mlx_set_cursor_mode(global->mlx, MLX_MOUSE_HIDDEN);
	get_derection_engel(info);
	load_texture(info);
	load_sprite_frames(info, global->mlx);
	return (global);
}

int	get_color(char c)
{
	if (c == '1' || c == ' ')
		return (get_rgb(109, 93, 110, 255));
	else if (c == 'D')
		return (get_rgb(79, 112, 156, 255));
	else if (c == 'd')
		return (get_rgb(33, 53, 85, 255));
	return (get_rgb(0, 0, 0, 255));
}

void	draw_square(mlx_image_t *image, int x, int y, int color)
{
	int x_tmp;
	int y_tmp;

	x_tmp = x;
	y_tmp = y;
	while (y < (y_tmp + SQUARE_LEN))
	{
		x = x_tmp;
		while (x < (x_tmp + SQUARE_LEN))
		{
			mlx_put_pixel_p(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_fov(t_global *pub, t_player *player)
{
	for (size_t i = 0; i < WIDTH; i++)
		draw_line(pub->window_img, player->pos, player->ray.pos);
}

void	draw_map(t_global *pub)
{
	t_loc	index;

	index.j = -1;
	index.i = -1;
	while (pub->info->map[++index.i])
	{
		index.j = -1;
		while (pub->info->map[index.i][++index.j])
			draw_square(pub->window_img
				, index.j * SQUARE_LEN
				, index.i * SQUARE_LEN
				, get_color(pub->info->map[index.i][index.j]));
	}
}

void	draw_dynamic_map(mlx_image_t *image, t_info *info)
{
	t_pos	map_pos;
	t_pos	pos_tmp;
	t_pos	pos;
	int		color;

	map_pos = info->player.pos;
	map_pos.y -= MINIMAP_SIZE / 2;
	map_pos.x -= MINIMAP_SIZE / 2;
	pos_tmp = map_pos;
	pos.x = 0;
	pos.y = 0;
	while (map_pos.y < (pos_tmp.y + MINIMAP_SIZE))
	{
		pos.x = 0;
		map_pos.x = pos_tmp.x;
		while (map_pos.x < (pos_tmp.x + MINIMAP_SIZE))
		{
			if ((map_pos.x >= 0 && map_pos.y >= 0)
					&& (map_pos.y < info->map_p_size.y && map_pos.x < info->map_p_size.x))
				color = get_color(info->map[(int)map_pos.y / SQUARE_LEN][(int)map_pos.x / SQUARE_LEN]);
			else
				color = get_color('1');
			mlx_put_pixel_p(image
					, pos.x, pos.y, color);
			map_pos.x++;
			pos.x++;
		}
		map_pos.y++;
		pos.y++;
	}
}

void	draw_rotation(mlx_image_t *image, t_player *player)
{
	t_pos	end;

	end.x = (MINIMAP_SIZE / 2) + (cos(player->rotation_angle) * 23);
	end.y = (MINIMAP_SIZE / 2) + (sin(player->rotation_angle) * 23);
	draw_line(image, (t_pos){.x = MINIMAP_SIZE / 2, .y = MINIMAP_SIZE / 2}, end);
}

void	minimap(t_global *pub)
{
	t_player	*player;

	player = &pub->info->player;
	draw_dynamic_map(pub->window_img, pub->info);
	draw_player(pub->window_img);
	draw_rotation(pub->window_img, player);
}
