/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:51:59 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/24 20:18:42 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "global.h"
# include "utils.h"
# include "libft.h"

/* **************** */
/*     PARSING      */
/* **************** */

t_info		*parsing(char *file_name);

bool		check_extension(char *file);
bool		isempty(char *file);
bool		isrgb(int rgb);
bool		isvalid_path(char *file);
t_list		*read_file(char *file);

bool		set_direction(char *data, char **direction);

bool		check_rgbform(char *rgb);
int			_set_color(char **color, int i, char *to_free);
bool		set_color(char *data, t_color *rgb);

void		set_datalen(t_list *file);
bool		info_isset(t_info *info);
bool		set_info(t_list **file, t_info *info);

bool		check_map(char **map);
t_list		*skip_newline(t_list *file);
int			get_bline(t_list *file);
char		*addsize(char *data, int len);
char		**to_matrix(t_list *file);
char		**parse_map(t_list *file);

/* **************** */
/*     MINIMAP      */
/* **************** */

void		set_newpos(t_global *pub);
void		handle_keys(mlx_key_data_t keydata, void *param);
t_global	*init_global(t_info *info);
int			get_color(char c);
void		draw_square(mlx_image_t *image, int x, int y, int color);
void		minimap(t_global *pub);
void		draw_player(mlx_image_t *image, t_info *info);
void		draw_line(mlx_image_t *image, t_pos start, t_pos end);


/* **************** */
/*     RAYCASTING   */
/* **************** */

t_pos	ray_cast(t_global *pub);
float	normalize_angle(float angle);

/* **************** */
/*     RENDERING    */
/* **************** */

void	draw_fc(t_global *pub);

#endif
