/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:51:59 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/27 23:01:39 by reben-ha         ###   ########.fr       */
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

bool	check_extension(char *file);
bool	isempty(char *file);
bool	isrgb(int rgb);
bool	isvalid_path(char *file);
t_list	*read_file(char *file);

bool	set_direction(char *data, char **direction);

bool	check_rgbform(char *rgb);
int		_set_color(char **color, int i, char *to_free);
bool	set_color(char *data, t_color *rgb);

void	set_datalen(t_list *file);
bool	info_isset(t_info *info);
void	set_info_defaut(t_info *info);
bool	set_info(t_list **file, t_info *info);

bool	check_newline(char **map);
t_list	*skip_newline(t_list *file);
int		get_bline(t_list *file);
char	*addsize(char *data, int len);
char	**to_matrix(t_list *file);
char	**parse_map(t_list *file);


#endif