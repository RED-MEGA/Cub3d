/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:08:40 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/16 21:27:00 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_info	*create_info(void)
{
	t_info	*info;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	info->f.r = FAIL;
	info->f.g = FAIL;
	info->f.b = FAIL;
	info->c.r = FAIL;
	info->c.g = FAIL;
	info->c.b = FAIL;
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
	if (info->no.path != NULL && info->so.path != NULL
		&& info->we.path != NULL && info->ea.path != NULL
		&& info->f.r != FAIL && info->f.g != FAIL
		&& info->f.b != FAIL && info->c.r != FAIL
		&& info->c.g != FAIL && info->c.b != FAIL)
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
		status = set_direction(buff, &(info->no));
	else if (ft_strncmp(buff, "SO ", 3) == 0)
		status = set_direction(buff, &(info->so));
	else if (ft_strncmp(buff, "WE ", 3) == 0)
		status = set_direction(buff, &(info->we));
	else if (ft_strncmp(buff, "EA ", 3) == 0)
		status = set_direction(buff, &(info->ea));
	else if (ft_strncmp(buff, "F ", 2) == 0)
		status = set_color(buff, &(info->f));
	else if (ft_strncmp(buff, "C ", 2) == 0)
		status = set_color(buff, &(info->c));
	else
		return (perror_x("Invalid identifier"), false);
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
	(*info)->door.path = ft_strdup("img/door.png");
	if (!isvalid_path((*info)->door.path)
		|| !check_extension((*info)->door.path, ".png"))
		return (perror_x("Invalid door path"), false);
	return (true);
}
