/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:40 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/28 06:23:16 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	info_isset(t_info *info)
{
	if (info->NO != NULL && info->SO != NULL
		&& info->WE != NULL && info->EA != NULL
		&& info->F.r != FAIL && info->F.g != FAIL
		&& info->F.b != FAIL && info->C.r != FAIL
		&& info->C.g != FAIL && info->C.b != FAIL)
		return (true);
	return (false);
}

void	set_info_defaut(t_info *info)
{
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
}

bool	set_info(t_list	**file, t_info *info)
{
	char	*buff;
	bool	status;

	status = true;
	while ((*file) && !info_isset(info) && status)
	{
		buff = ft_strtrim((*file)->data, " ");
		if (buff[0] == '\0')
			;
		else if (ft_strncmp(buff, "NO ", 3) == 0)
			status = set_direction(buff, &(info->NO));
		else if (ft_strncmp(buff, "SO ", 3) == 0)
			status = set_direction(buff, &(info->SO));
		else if (ft_strncmp(buff, "WE ", 3) == 0)
			status = set_direction(buff, &(info->WE));
		else if (ft_strncmp(buff, "EA ", 3) == 0)
			status = set_direction(buff, &(info->EA));
		else if (ft_strncmp(buff, "F ", 2) == 0)
			status = set_color(buff, &(info->F));
		else if (ft_strncmp(buff, "C ", 2) == 0)
			status = set_color(buff, &(info->C));
		(*file) = (*file)->next;
	}
	if (!info_isset(info))
		return (perror_x("Some attribute not set")
			, false);
	return (status);
}

void	set_datalen(t_list *file)
{
	while (file)
	{
		file->len = ft_strlen(file->data);
		file = file->next;
	}
}

bool	check_newline(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		if (map[i][0] == '\n')
			return (true);
	return (false);
}
