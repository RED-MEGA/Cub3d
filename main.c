/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/26 13:50:01 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/global.h"

bool	check_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (compare(extension, ".cub"))
		return (true);
	return (false);
}

char	**read_file(char *map_file)
{
	char	*file_data;
	char	*buff;
	int		fd;

	file_data = NULL;
	fd = open(map_file, O_RDONLY);
	ft_error(fd, 1);

	buff = get_next_line(fd);
	if (!buff)
		ft_error_msg("Empty file", 1);
	while (buff != NULL)
	{
		file_data = ft_strjoin_gnl(file_data, buff);
		free(buff);
		buff = get_next_line(fd);
	}
	printf("%s\n", file_data);
	return (ft_split(file_data, '\n'));
}

void	cub3d(char *map_file)
{
	char	**file;

	if (check_extension(map_file))
		ft_error_msg(ERRFILE, EXIT_FAILURE);
	file = read_file(map_file);
	ft_error_ptr(file, 1);
	
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
