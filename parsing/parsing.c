/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:46:12 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/31 18:28:47 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_info	*create_info(void)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	ft_error_ptr(info, EXIT_FAILURE);
	info->NO = NULL;
	info->SO = NULL;
	info->WE = NULL;
	info->EA = NULL;
	info->F.r = FAIL;
	info->F.g = FAIL;
	info->F.b = FAIL;
	info->C.r = FAIL;
	info->C.g = FAIL;
	info->C.b = FAIL;
	return (info);
}

t_info	*parsing(char *file_name)
{
	t_list	*file;
	t_info	*info;

	if (!check_extension(file_name))
		ft_error_msg(ERRFILE, EXIT_FAILURE);
	if (isempty(file_name))
		ft_error_msg(ERREMPTY, EXIT_FAILURE);
	file = read_file(file_name); // Note : Check leak
	info = create_info();
	if (!set_info(&file, info))
		return (ft_lstclear(&file), free(info)
				, exit(EXIT_FAILURE), NULL);
	set_datalen(file);
	info->map = parse_map(skip_newline(file));
	if (!info->map || !check_map(info->map))
		return (free(info), ft_error_msg("Invalid map", 1)
				, NULL);
	return (info);
}
