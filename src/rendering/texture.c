/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:33:44 by azarda            #+#    #+#             */
/*   Updated: 2023/09/16 21:27:19 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_img *image)
{
	unsigned int	*buff;
	mlx_texture_t	*img;
	unsigned int	i;
	unsigned int	j;

	img = mlx_load_png(image->path);
	if (!img)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	image->height = img->height;
	image->width = img->width;
	buff = (unsigned int *)malloc(img->width * img->height
			* sizeof(unsigned int));
	ft_error_ptr(buff, 1);
	i = 0;
	j = 0;
	while (j < img->width * img->height)
	{
		buff[j++] = get_rgb(img->pixels[i],
				img->pixels[i + 1], img->pixels[i + 2], 255);
		i += 4;
	}
	mlx_delete_texture(img);
	image->buffer_img = buff;
}

void	load_texture(t_info *info)
{
	init_texture(&info->no);
	init_texture(&info->so);
	init_texture(&info->we);
	init_texture(&info->ea);
	init_texture(&info->door);
}

static mlx_texture_t	*load_frame(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		ft_error_msg(mlx_strerror(mlx_errno), 1);
	return (texture);
}

void	load_sprite_frames(t_info *info)
{
	info->weapon[0] = load_frame("img/Mjollnir_in_normal.png");
	info->weapon[1] = load_frame("img/Mjollnir_in_attack.png");
	info->sprite[0] = load_frame("img/sprite_frames/frame_00.png");
	info->sprite[1] = load_frame("img/sprite_frames/frame_01.png");
	info->sprite[2] = load_frame("img/sprite_frames/frame_02.png");
	info->sprite[3] = load_frame("img/sprite_frames/frame_03.png");
	info->sprite[4] = load_frame("img/sprite_frames/frame_04.png");
	info->sprite[5] = load_frame("img/sprite_frames/frame_05.png");
	info->sprite[6] = load_frame("img/sprite_frames/frame_06.png");
	info->sprite[7] = load_frame("img/sprite_frames/frame_07.png");
	info->sprite[8] = load_frame("img/sprite_frames/frame_08.png");
	info->sprite[9] = load_frame("img/sprite_frames/frame_09.png");
}

t_img	ft_img_render(t_global *pub)
{
	t_img	img;

	if (pub->de.down && pub->info->player.ray.flag == 1 \
	&& pub->info->player.ray.dor == 0)
		img = pub->info->so;
	else if (pub->de.up && pub->info->player.ray.flag == 1 \
	&& pub->info->player.ray.dor == 0)
		img = pub->info->no;
	else if (pub->de.left && pub->info->player.ray.flag == 2 \
	&& pub->info->player.ray.dor == 0)
		img = pub->info->ea;
	else if (pub->de.right && pub->info->player.ray.flag == 2 \
	&& pub->info->player.ray.dor == 0)
		img = pub->info->we;
	else
		img = pub->info->door;
	return (img);
}
