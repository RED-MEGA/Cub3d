/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:27:54 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/28 21:10:20 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	check_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
		if (map[i][0] == '\n')
			return (false);
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
	   		if (map[i][j] != '0'
				&& map[i][j] != '1'
				&& map[i][j] != 'N'
				&& map[i][j] != 'S'
				&& map[i][j] != 'E'
				&& map[i][j] != 'W'
				&& map[i][j] != ' ')
				return (false);
	}
	
	int	player_set = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N'
				|| map[i][j] == 'S'
				|| map[i][j] == 'E'
				|| map[i][j] == 'W')
				player_set++;
		}
	}
	if (player_set > 1)
		return (false);
	

	j = -1;
	while (map[0][++j])
		if (map[0][j] == '0')
			return (false);

	i--;
	j = -1;
	while (map[i] && map[i][++j])
		if (map[i][j] == '0')
			return (false);
	




	i = 0;
	while (map[++i] && map[i + 1] != NULL)
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' && (j == 0
				|| (map[i + 1][j] == ' '
				|| map[i - 1][j] == ' '
				|| map[i][j + 1] == ' '
				|| map[i][j - 1] == ' '
				|| map[i][j + 1] == '\0')))
				return (false);
		}
	}







	return (true);
}
