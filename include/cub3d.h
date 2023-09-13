/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:51:59 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/13 22:05:27 by reben-ha         ###   ########.fr       */
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

t_info		*parsing(char *file_name);

t_info	*create_info(void);
bool	info_isset(t_info *info);
bool	set_info(t_list	**file, t_info *info);
bool	init_info(t_info **info, t_list **file);

void	init_player(t_info *info);

bool		check_extension(char *file, char *extension);
bool		isempty(char *file);
bool		isrgb(int rgb);
bool		isvalid_path(char *file);
t_list		*read_file(char *file);

bool		set_direction(char *data, t_img *image);

bool		check_rgbform(char *rgb);
int			_set_color(char **color, int i, char *to_free);
bool		set_color(char *data, t_color *rgb);

void		set_datalen(t_list *file);

bool		check_map(t_info *info);
t_list		*skip_newline(t_list *file);
int			get_bline(t_list *file);
char		*addsize(char *data, int len);
char		**to_matrix(t_list *file);
bool		parse_map(t_info *info, t_list *file);

/* **************** */
/*     MINIMAP      */
/* **************** */

void		set_newpos(t_info *info, t_player *player);
void		handle_keys(mlx_key_data_t keydata, void *param);
void		handle_cursor(double xpos, double ypos, void *param);
t_global	*init_global(t_info *info);
int			get_color(char c);
void		draw_square(mlx_image_t *image, int x, int y, int color);
void		minimap(t_global *pub);
void		draw_player(mlx_image_t *image);

/* **************** */
/*     RAYCASTING   */
/* **************** */


t_pos		ft_horizontal_inter(t_global *pub, t_player player, int *dor);
t_pos		ft_vertical_inter(t_global *pub, t_player player, int *dor);
t_pos		ray_cast(t_global *pub, int *flag, int *dor);





/* **************** */
/*     RENDERING    */
/* **************** */

void 			load_texture(t_info *info);
void			to_3d_ray(t_global *pub, int i, double wall_height, int y);
double			calcul_wp(t_player *player);
void			calcul_ray(t_global *pub, t_player *player);
void			render(t_global *pub);
void			draw_fc(mlx_image_t *image, t_color color, t_pos pos);


void	check_dor_close(t_global	*pub);
void	check_dor_open(t_global	*pub);
void	handle_mouse(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
bool	wall_collision(char **map, t_pos *oldpos, t_pos *newpos);

void	mjollnir(t_global *pub);

#endif
