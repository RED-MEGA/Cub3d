/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:27:54 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/31 08:42:12 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	m_check_characters(char **map)
{
	int	i;
	int	j;
	
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
	return (true);
}

bool	m_check_playerc(char **map)
{
	int	i;
	int	j;
	int	player_set;

	player_set = 0;
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
	if (player_set != 1)
		return (false);
	return (true);
}

bool	m_check_tb(int i, char **map)
{	
	int	j;

	j = -1;
	while (map[0][++j])
		if (map[0][j] == '0')
			return (false);
	j = -1;
	while (map[i] && map[i][++j])
		if (map[i][j] == '0')
			return (false);
	return (true);
}

bool	m_check_surrounded(char **map)
{
	int i;
	int j;

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

bool	check_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
		if (map[i][0] == '\n')
			return (false);
	if (!m_check_characters(map)
		|| !m_check_playerc(map)
		|| !m_check_tb(--i, map)
		|| !m_check_surrounded(map))
		return (false);
	return (true);
}
