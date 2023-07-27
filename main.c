/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/27 23:09:21 by reben-ha         ###   ########.fr       */
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



	// for (size_t i = 0; file; file = file->next)
	// {
	// 	printf("%s:newline\n", file->data);
	// }
	// exit(1);



	printf("\nAttribute : \n");
	printf("NO : %s \n", info.NO);
	printf("SO : %s \n", info.SO);
	printf("WE : %s \n", info.WE);
	printf("EA : %s \n", info.EA);
	printf("F : (%d,%d,%d) \n", info.F.r, info.F.g, info.F.b);
	printf("C : (%d,%d,%d) \n", info.C.r, info.C.g, info.C.b);




	printf("\nMap : Before parse\n");
	for (t_list *tmp = file; tmp; tmp = tmp->next)
		printf("%s:newline\n", tmp->data);



	set_datalen(file);
	info.map = parse_map(skip_newline(file));
	if (!info.map && check_newline(info.map))
		ft_error_msg("Invalid map", 1);

	// if (!info.map && check_newline(info.map))
	// 	ft_error_msg("Invalid map", 1);
	



	
	printf("\nMap : After parse\n");
	
	for (size_t i = 0; info.map[i]; i++)
	{
		printf("%s:newline\n", info.map[i]);
	}
	
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (perror_x(ERRINVALID), 1);
	cub3d(argv[1]);
	return (0);
}
