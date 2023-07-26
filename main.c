/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/26 11:24:47 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/global.h"

bool	check_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (compare(extension, ".cub"))
		return (true);
	return (true);
}

void	cub3d(char *map_file)
{
	if (check_extension(map_file))
		ft_error_msg(ERRFILE, EXIT_FAILURE);
	
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
