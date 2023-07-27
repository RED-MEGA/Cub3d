/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/27 00:43:17 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

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
		ft_lstadd_back(&file_data, ft_lstnew(buff));
	}
	close(fd);
	return (file_data);
}

bool	isrgb(int rgb)
{
	if (rgb >= 0 && rgb <= 255)
		return (true);
	return (false);
}

bool	set_info(t_list	*file, t_info *info)
{
	char	**data;
	char	*color;
	int		rgb;

	while (file)
	{
		if (file->data[0] == '\n')
			;
		else if (ft_strncmp(file->data, "NO ", 3))
		{
			data = ft_split(file->data, ' ');
			(*info).NO = ft_strdup(data[1]);
			ft_free(data);
		}
		else if (ft_strncmp(file->data, "SO ", 3))
		{
			data = ft_split(file->data, ' ');
			(*info).SO = ft_strdup(data[1]);
			ft_free(data);
		}
		else if (ft_strncmp(file->data, "WE ", 3))
		{
			data = ft_split(file->data, ' ');
			(*info).WE = ft_strdup(data[1]);
			ft_free(data);
		}
		else if (ft_strncmp(file->data, "EA ", 3))
		{
			data = ft_split(file->data, ' ');
			(*info).EA = ft_strdup(data[1]);
			ft_free(data);
		}
		else if (ft_strncmp(file->data, "F ", 2))
		{
			data = ft_split(file->data, ' ');
			color = ft_split(data[1], ',');
			ft_free(data);

			rgb = ft_atoi(color[0]);
			if (isrgb(rgb))
				return (ft_free(color), ft_error_msg("Wrong RGB range", 1), false);
			(*info).F.r = isrgb(ft_atoi(color[0]));
			
			rgb = ft_atoi(color[1]);
			if (isrgb(rgb))
				return (ft_free(color), ft_error_msg("Wrong RGB range", 1), false);
			(*info).F.g = isrgb(ft_atoi(color[1]));

			rgb = ft_atoi(color[2]);
			if (isrgb(rgb))
				return (ft_free(color), ft_error_msg("Wrong RGB range", 1), false);
			(*info).F.b = isrgb(ft_atoi(color[2]));

			ft_free(color);
		}
		else if (ft_strncmp(file->data, "C ", 2))
		{
			data = ft_split(file->data, ' ');
			color = ft_split(data[1], ',');
			ft_free(data);

			rgb = ft_atoi(color[0]);
			if (isrgb(rgb))
				return (ft_free(color), ft_error_msg("Wrong RGB range", 1), false);
			(*info).C.r = isrgb(ft_atoi(color[0]));
			
			rgb = ft_atoi(color[1]);
			if (isrgb(rgb))
				return (ft_free(color), ft_error_msg("Wrong RGB range", 1), false);
			(*info).C.g = isrgb(ft_atoi(color[1]));

			rgb = ft_atoi(color[2]);
			if (isrgb(rgb))
				return (ft_free(color), ft_error_msg("Wrong RGB range", 1), false);
			(*info).C.b = isrgb(ft_atoi(color[2]));

			ft_free(color);
		}
		file = file->next;
	}


	return (true);
}

void	cub3d(char *map_file)
{
	t_list	*file;
	t_info	info;

	if (!check_extension(map_file))
		ft_error_msg(ERRFILE, EXIT_FAILURE);
	if (isempty(map_file))
		ft_error_msg("Empty file", EXIT_FAILURE);
	file = read_file(map_file);
	// for (t_list *tmp = file; tmp; tmp = tmp->next)
	// {
	// 	printf("%s", tmp->data);
	// }
	
	if (!set_info(file, &info))
		ft_error_msg("Invalid info", EXIT_FAILURE);
	
		
	

	











	

	








}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
