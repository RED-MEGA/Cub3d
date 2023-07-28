/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/28 18:57:41 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

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
	set_info_defaut(&info);
	if (!set_info(&file, &info))
		return (ft_lstclear(&file), exit(EXIT_FAILURE));

	set_datalen(file);
	info.map = parse_map(skip_newline(file));
	if (!info.map || !check_map(info.map))
		ft_error_msg("Invalid map", 1);

















	
	
	int debug_fd = open("Debug.log", O_RDWR);
	dprintf(debug_fd, "/* **************** */\n");
	dprintf(debug_fd, "/*     PARSING      */\n");
	dprintf(debug_fd, "/* **************** */\n");
	dprintf(debug_fd, "\nAttribute : \n");
	dprintf(debug_fd, "NO : %s \n", info.NO);
	dprintf(debug_fd, "SO : %s \n", info.SO);
	dprintf(debug_fd, "WE : %s \n", info.WE);
	dprintf(debug_fd, "EA : %s \n", info.EA);
	dprintf(debug_fd, "F : (%d,%d,%d) \n", info.F.r, info.F.g, info.F.b);
	dprintf(debug_fd, "C : (%d,%d,%d) \n", info.C.r, info.C.g, info.C.b);

	dprintf(debug_fd, "\nMap :\n");
	for (size_t i = 0; info.map[i]; i++)
		dprintf(debug_fd, "%s:newline\n", info.map[i]);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
