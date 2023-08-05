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
	info->player.rotation_angle = 0;
	return (info);
}

void	_set_pi(char **map, t_player *player, char c, t_loc pos)
{
	player->pos.x = pos.j * SQUARE_LEN;
	player->pos.y = pos.i * SQUARE_LEN;
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
	t_player	player;
	t_loc		loc;
	int			i;
	int			j;

	loc.i = -1;
	loc.j = -1;
	while (info->map[++loc.i])
	{
		loc.j = -1;
		while (info->map[loc.i][++loc.j])
		{
			if (info->map[loc.i][loc.j] == 'N' || info->map[loc.i][loc.j] == 'S'
				|| info->map[loc.i][loc.j] == 'W' || info->map[loc.i][loc.j] == 'E')
			{
				_set_pi(info->map, &info->player 
						, info->map[loc.i][loc.j]
						, loc);
				break ;
			}
		}
	}
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
	info->map_size.y = ft_matlen(info->map) * SQUARE_LEN;
	info->map_size.x = ft_strlen(info->map[0]) * SQUARE_LEN;
	set_player_info(info);
	return (info);
}
