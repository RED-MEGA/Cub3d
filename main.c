/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/27 17:42:50 by reben-ha         ###   ########.fr       */
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
		ft_lstadd_back(&file_data, ft_lstnew(ft_substr(buff, 0, ft_strlen(buff) - 1)));
		free(buff);
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

bool	isvalid_path(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == FAIL)
		return (false);
	return (close(fd), true);
}

bool	set_direction(char *data, char **direction)
{
	char	*buff;

	buff = ft_strtrim(data + 3, " ");
	if (!isvalid_path(buff))
		return (free(data), free(buff)
			, perror_x("Invalid direction attribute")
			, false);
	(*direction) = buff;
	return (free(data), true);
}

bool	check_rgbform(char *rgb)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (rgb[++i])
		if (rgb[i] == ',')
			count++;
	if (count != 2)
		return (false);
	i = -1;
	while (rgb[++i])
		if (!ft_isdigit(rgb[i]) && rgb[i] != ',')
			return (false);
	return (true);	
}

int		_set_color(char **color, int i, char *to_free)
{
	int	nb;

	nb = ft_atoi(color[i]);
	if (!isrgb(nb))
		return (free(to_free), ft_free(color)
			, ft_error_msg("Wrong RGB range", 1), false);
	return (nb);
}

bool	set_color(char *data, t_color *rgb)
{
	char	*buff;
	char	**color;

	buff = ft_strtrim(data + 2, " ");
	if (!check_rgbform(buff))
		return (free(data), free(buff), perror_x("Invalid color attribute"), false);
	color = ft_split(buff, ',');
	free(buff);
	rgb->r = _set_color(color, 0, data);
	rgb->g = _set_color(color, 1, data);
	rgb->b = _set_color(color, 2, data);
	ft_free(color);
	return (free(data), true);
}

bool	info_isset(t_info *info)
{
	if (info->NO != NULL && info->SO != NULL
		&& info->WE != NULL && info->EA != NULL
		&& info->F.r != FAIL && info->F.g != FAIL
		&& info->F.b != FAIL && info->C.r != FAIL
		&& info->C.g != FAIL && info->C.b != FAIL)
		return (true);
	return (false);
}

void	set_info_defaut(t_info *info)
{
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
}

bool	set_info(t_list	**file, t_info *info)
{
	char	*buff;
	bool	status;

	status = true;
	while ((*file) && !info_isset(info) && status)
	{
		buff = ft_strtrim((*file)->data, " ");
		if (buff[0] == '\0')
			;
		else if (ft_strncmp(buff, "NO ", 3) == 0)
			status = set_direction(buff, &(info->NO));
		else if (ft_strncmp(buff, "SO ", 3) == 0)
			status = set_direction(buff, &(info->SO));
		else if (ft_strncmp(buff, "WE ", 3) == 0)
			status = set_direction(buff, &(info->WE));
		else if (ft_strncmp(buff, "EA ", 3) == 0)
			status = set_direction(buff, &(info->EA));
		else if (ft_strncmp(buff, "F ", 2) == 0)
			status = set_color(buff, &(info->F));
		else if (ft_strncmp(buff, "C ", 2) == 0)
			status = set_color(buff, &(info->C));
		(*file) = (*file)->next;
	}
	if (!info_isset(info))
		return (perror_x("Some attribute not set")
			, false);
	return (status);
}

t_list	*skip_newline(t_list *info)
{
	while (info && info->data[0] == '\0')
		info = info->next;
	return (info);
}

int	get_bline(t_list *file)
{
	int topline;

	topline = ft_strlen(file->data);
	file = file->next;
	while (file)
	{
		if (ft_strlen(file->data) > topline)
			topline = ft_strlen(file->data);
		file = file->next;
	}
	return (topline);
}

char	*addsize(char *data, int len)
{
	char	*newstr;
	char	*spaces;
	int		i;

	spaces = (char *)malloc(len * sizeof(char) + 1);
	ft_error_ptr(spaces, 1);
	i = -1;
	spaces[len] = '\0';
	while (spaces[++i])
		spaces[i] = ' ';
	newstr = ft_strjoin_gnl(data, spaces);
	return (free(spaces), newstr);
}

char	**to_matrix(t_list *file)
{
	int		i;
	int		list_size;
	char	**map;

	map = NULL;
	list_size = ft_lstsize(file);
	map = (char **)malloc(sizeof(char *) * list_size);
	map[list_size] = NULL;
	i = -1;
	while (file)
	{
		map[++i] = ft_strdup(file->data);
		file = file->next;
	}
	return (ft_lstclear(&file), map);
}

char	**parse_map(t_list *file)
{
	int	bline;

	bline = get_bline(file);
	while (file)
	{
		if (bline < ft_strlen(file->data))
			file->data = addsize(file->data, bline - ft_strlen(file->data));
		file = file->next;
	}
	return (to_matrix(file));
}

void	cub3d(char *map_file)
{
	t_list	*file;
	t_list	*head;
	t_info	info;

	if (!check_extension(map_file))
		ft_error_msg(ERRFILE, EXIT_FAILURE);
	if (isempty(map_file))
		ft_error_msg("Empty file", EXIT_FAILURE);
	file = read_file(map_file);



	// for (size_t i = 0; file; file = file->next)
	// {
	// 	printf("%s:newline\n", file->data);
	// }
	// exit(1);


	set_info_defaut(&info);
	if (!set_info(&file, &info))
		return (ft_lstclear(&file), exit(EXIT_FAILURE));

	printf("\nAttribute : \n");
	printf("NO : %s \n", info.NO);
	printf("SO : %s \n", info.SO);
	printf("WE : %s \n", info.WE);
	printf("EA : %s \n", info.EA);
	printf("F : (%d,%d,%d) \n", info.F.r, info.F.g, info.F.b);
	printf("C : (%d,%d,%d) \n", info.C.r, info.C.g, info.C.b);




	printf("\nMap : Before parse\n");
	for (t_list *tmp = file; tmp; tmp = tmp->next)
		printf("%s\n", tmp->data);

	
	
	info.map = parse_map(skip_newline(file));
	if (!info.map)
		return ;





	
	

	printf("\nMap : After parse\n");
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
