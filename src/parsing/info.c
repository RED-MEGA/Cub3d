/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:40 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/15 16:16:36 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_info	*create_info(void)
{
	t_info	*info;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	info->F.r = FAIL;
	info->F.g = FAIL;
	info->F.b = FAIL;
	info->C.r = FAIL;
	info->C.g = FAIL;
	info->C.b = FAIL;
	info->player.pos.x = FAIL;
	info->player.pos.y = FAIL;
	info->player.direction = FAIL;
	info->player.move_v = NONE;
	info->player.move_h = NONE;
	info->player.sprint = false;
	info->player.attack = false;
	return (info);
}

static bool	info_isset(t_info *info)
{
	if (info->NO.path != NULL && info->SO.path != NULL
		&& info->WE.path != NULL && info->EA.path != NULL
		&& info->F.r != FAIL && info->F.g != FAIL
		&& info->F.b != FAIL && info->C.r != FAIL
		&& info->C.g != FAIL && info->C.b != FAIL)
		return (true);
	return (false);
}

static bool	select_option(t_info *info, char *buff)
{
	bool	status;

	status = true;
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
	else
		return (perror_x("Invalid identifier"), free(buff), false);
	return (status);
}

static bool	set_info(t_list	**file, t_info *info)
{
	char	*buff;
	bool	status;

	status = true;
	while ((*file) && !info_isset(info) && status)
	{
		buff = ft_strtrim((*file)->data, " ");
		status = select_option(info, buff);
		(*file) = (*file)->next;
		free(buff);
	}
	return (status);
}

bool	init_info(t_info **info, t_list **file)
{
	*info = create_info();
	if (!set_info(file, *info))
		return (false);
	if (!info_isset(*info))
		return (perror_x("Some attribute not set")
			, false);
	(*info)->DOOR.path = ft_strdup("img/door.png");
	if (!isvalid_path((*info)->DOOR.path)
		|| !check_extension((*info)->DOOR.path, ".png"))
		return (perror_x("Invalid door path"), false);
	return (true);
}
