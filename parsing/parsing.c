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

t_info	*create_info(void)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	ft_error_ptr(info, EXIT_FAILURE);
	info->NO = NULL;
	info->SO = NULL;
	info->WE = NULL;
	info->EA = NULL;
	info->map = NULL;
	info->F.r = FAIL;
	info->F.g = FAIL;
	info->F.b = FAIL;
	info->C.r = FAIL;
	info->C.g = FAIL;
	info->C.b = FAIL;
	info->player.pos.x = FAIL;
	info->player.pos.y = FAIL;
	info->player.direction = FAIL;
	info->player.turn_d = 0;
	info->player.walk_d = 0;
	info->player.move_v = NONE;
	info->player.move_h = NONE;
	info->player.rotation_angle = 0;
	return (info);
}

void	_set_pi(char **map, t_player *player, char c, t_loc pos)
{
	player->pos.x = (pos.j * SQUARE_LEN) + (SQUARE_LEN / 2);
	player->pos.y = (pos.i * SQUARE_LEN) + (SQUARE_LEN / 2);
	map[pos.i][pos.j] = 'P';
	if (c == 'N')
		player->direction = NO;
	else if (c == 'S')
		player->direction = SO;
	else if (c == 'W')
		player->direction = WE;
	else if (c == 'E')
		player->direction = EA;
}

void	set_player_info(t_info *info)
{
	t_loc		loc;

	loc.i = -1;
	loc.j = -1;
	while (info->map[++loc.i])
	{
		loc.j = -1;
		while (info->map[loc.i][++loc.j])
		{
			if (info->map[loc.i][loc.j] == 'P')
			{
				_set_pi(info->map, &info->player 
						, info->player.key
						, loc);
				break ;
			}
		}
	}
}

bool	init_info(t_info **info, t_list **file)
{
	bool	status;

	status = true;
	*info = create_info();
	status = set_info(file, *info);
	if (!info_isset(*info))
		return (perror_x("Some attribute not set")
			, false);
	return (status);
}

t_info	*parsing(char *file_name)
{
	t_list	*file;
	t_list	*tmp;
	t_info	*info;
	bool	status;

	if (!check_extension(file_name))
		ft_error_msg(ERRFILE, EXIT_FAILURE);
	if (isempty(file_name))
		ft_error_msg(ERREMPTY, EXIT_FAILURE);
	file = read_file(file_name); // Note : Check leak
	tmp = file;
	status = init_info(&info, &file);
	if (!status)
		return (ft_lstclear(&tmp), exit(EXIT_FAILURE), NULL);
	set_datalen(file);
	status = parse_map(info, skip_newline(file));
	ft_lstclear(&tmp);
	if (!status)
		return (ft_error_msg("Invalid map", 1), NULL);
	set_player_info(info);
	return (info);
}
