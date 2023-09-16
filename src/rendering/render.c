/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:28:09 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/16 18:24:47 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calcul_wp(t_player *player)
{
	double	a;
	double	b;
	double	d;

	a = (double)SQUARE_LEN;
	b = player->ray.len * cos(player->rotation_angle - player->ray.angle);
	d = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	return ((a / b) * d);
}

static int	calcul_ofset_x(t_ray ray, t_img img)
{
	int	ofset_x;

	ofset_x = 0;
	if (ray.flag == 1)
		ofset_x = (ray.pos.x / SQUARE_LEN - \
		(int)ray.pos.x / SQUARE_LEN) * img.width;
	else if (ray.flag == 2)
		ofset_x = (ray.pos.y / SQUARE_LEN - \
		(int)ray.pos.y / SQUARE_LEN) * img.width;
	return (ofset_x);
}

static void	to_3d_ray(t_global *pub, int i, 
			double wall_height, t_loc *range)
{
	t_img	img;
	t_loc	ofset;
	int		color;
	int		y;

	y = -1;
	img = ft_img_render(pub);
	ofset.j = calcul_ofset_x(pub->info->player.ray, img);
	while (++y < HEIGHT)
	{
		if (y < range->i)
			color = get_rgb(pub->info->C.r, pub->info->C.g, pub->info->C.b,
					255);
		else if (y >= range->i && y < range->j)
		{
			ofset.i = (y - range->i) * ((double)img.height / wall_height);
			color = (img.buffer_img[(img.width * ofset.i) + ofset.j]);
		}
		else if (y > range->j)
			color = get_rgb(pub->info->F.r, pub->info->F.g, pub->info->F.b,
					255);
		mlx_put_pixel_p(pub->window_img, i, y, color);
	}
}

static void	calcul_ray(t_global *pub, t_player *player)
{
	player->ray.dor = 0;
	player->ray.pos = ray_cast(pub, &(player->ray.flag), &(player->ray.dor));
	player->ray.angle = player->ray_angle;
	player->ray.len = calcul_distance(player->pos, player->ray.pos);
}

void	render(t_global *pub)
{
	t_player	*player;
	t_loc		range;
	double		wall_height;
	int			i;

	i = -1;
	player = &(pub->info->player);
	player->ray_angle = normalize_angle(player->rotation_angle
			- (FOV_ANGLE / 2));
	while (++i < WIDTH)
	{
		calcul_ray(pub, player);
		wall_height = calcul_wp(player);
		range.i = (HEIGHT / 2) - (wall_height / 2);
		range.j = (HEIGHT / 2) + (wall_height / 2);
		to_3d_ray(pub, i, wall_height, &range);
		player->ray_angle = normalize_angle(player->ray_angle + RAY_D);
		player->ray.dor = 0;
	}
}
