/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:51:59 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/16 18:47:10 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "global.h"
# include "tools.h"
# include "libft.h"

/* **************** */
/*     PARSING      */
/* **************** */

bool		set_direction(char *data, t_img *image);
bool		set_color(char *data, t_color *rgb);
bool		check_extension(char *file, char *extension);
bool		isempty(char *file);
bool		isrgb(int rgb);
bool		isvalid_path(char *file);
bool		init_info(t_info **info, t_list **file);
bool		check_map(t_info *info);
bool		parse_map(t_info *info, t_list *file);
void		init_player(t_info *info);
t_list		*read_file(char *file);
t_global	*init_global(t_info *info);
t_list		*skip_newline(t_list *file);
t_info		*parsing(char *file_name);

/* **************** */
/*     RAYCASTING   */
/* **************** */

t_pos		ft_horizontal_inter(t_global *pub, t_player player, int *dor);
t_pos		ft_vertical_inter(t_global *pub, t_player player, int *dor);
t_pos		ray_cast(t_global *pub, int *flag, int *dor);

/* **************** */
/*     RENDERING    */
/* **************** */

void		update_position(t_info *info, t_player *player);
void		minimap(t_global *pub);
void		render(t_global *pub);
void		mjollnir(t_global *pub);
void		load_texture(t_info *info);
void		load_sprite_frames(t_info *info);
t_img		ft_img_render(t_global *pub);

/* **************** */
/*       HOOKS      */
/* **************** */

bool		handle_turn(t_player *player, mlx_key_data_t keydata);
bool		handle_moves(t_player *player, mlx_key_data_t keydata);
bool		handle_features(t_global *pub, mlx_key_data_t keydata);
bool		key_press(mlx_key_data_t keydata, keys_t key);
bool		key_release(mlx_key_data_t keydata, keys_t key);
void		close_door(t_global *pub);
void		open_door(t_global *pub);
void		handle_keys(mlx_key_data_t keydata, void *param);
void		handle_cursor(double xpos, double ypos, void *param);
void		handle_mouse(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);

#endif
