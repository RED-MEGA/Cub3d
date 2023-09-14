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

#include "cub3d.h"

static void	set_datalen(t_list *file)
{
	while (file)
	{
		file->len = ft_strlen(file->data);
		file = file->next;
	}
}

t_info	*parsing(char *file_name)
{
	t_list	*file;
	t_list	*tmp;
	t_info	*info;
	bool	status;

	if (!check_extension(file_name, ".cub"))
		ft_error_msg(ERRFILE, EXIT_FAILURE);
	if (isempty(file_name))
		ft_error_msg(ERREMPTY, EXIT_FAILURE);
	file = read_file(file_name);
	tmp = file;
	status = init_info(&info, &file);
	if (!status)
		return (ft_lstclear(&tmp), exit(EXIT_FAILURE), NULL);
	set_datalen(file);
	status = parse_map(info, skip_newline(file));
	ft_lstclear(&tmp);
	if (!status)
		return (ft_error_msg("Invalid map", 1), NULL);
	init_player(info);
	return (info);
}
