/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:47:39 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/01 19:54:26 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
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

bool	isrgb(int rgb)
{
	if (rgb >= 0 && rgb <= 255)
		return (true);
	return (false);
}

bool	isvalid_path(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == FAIL)
		return (false);
	return (close(fd), true);
}

t_list	*read_file(char *file)
{
	t_list	*file_data;
	char	*buff;
	int		fd;

	file_data = NULL;
	fd = open(file, O_RDONLY);
	ft_error(fd, 1);
	while (1)
	{
		buff = get_next_line(fd);
		if (!buff)
			break ;
		if (buff[ft_strlen(buff) - 1] != '\n')
			buff = ft_strjoin_gnl(buff, "\n");
		ft_lstadd_back(&file_data, ft_lstnew(ft_substr(buff, 0, ft_strlen(buff) - 1)));
		free(buff);
	}
	close(fd);
	return (file_data);
}
