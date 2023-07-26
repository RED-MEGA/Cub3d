/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/26 16:31:05 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

bool	check_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (compare(extension, ".cub"))
		return (true);
	return (false);
}

bool	isempty(char *file)
{
	char	*buff;
	int		fd;

	fd = open(file, O_RDONLY);
	ft_error(fd, 1);
	buff = get_next_line(fd);
	if (!buff)
		return (true);
	free(buff);
	close(fd);
	return (false);
}

t_list	*read_file(char *map_file)
{
	t_list	*file_data;
	char	*buff;
	int		fd;

	file_data = NULL;
	fd = open(map_file, O_RDONLY);
	ft_error(fd, 1);
	while (1)
	{
		buff = get_next_line(fd);
		if (!buff)
			break ;
		ft_lstadd_back(&file_data, ft_lstnew(buff));
	}
	close(fd);
	return (file_data);
}

void	cub3d(char *map_file)
{
	t_list	*file;

	if (!check_extension(map_file))
		ft_error_msg(ERRFILE, EXIT_FAILURE);
	if (isempty(map_file))
		ft_error_msg("Empty file", EXIT_FAILURE);
	
	file = read_file(map_file);



	
	for (t_list *tmp = file; tmp; tmp = tmp->next)
	{
		printf("%s", tmp->data);
	}
	








}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
