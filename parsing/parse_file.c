/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:46:12 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/31 17:53:36 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_info	*parse_file(char *file_name)
{
	t_list	*file;
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!check_extension(file_name))
		ft_error_msg(ERRFILE, EXIT_FAILURE);
	if (isempty(file_name))
		ft_error_msg("Empty file", EXIT_FAILURE);
	file = read_file(file_name);
	set_info_defaut(info);
	if (!set_info(&file, info))
		return (ft_lstclear(&file), exit(EXIT_FAILURE), NULL);
	set_datalen(file);
	info->map = parse_map(skip_newline(file));
	if (!info->map || !check_map(info->map))
		ft_error_msg("Invalid map", 1);
	return (info);
}
