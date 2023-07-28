/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:11:17 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/28 06:22:39 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_list	*skip_newline(t_list *file)
{
	while (file && file->data[0] == '\0')
		file = file->next;
	return (file);
}

int		get_bline(t_list *file)
{
	int topline;

	topline = file->len;
	file = file->next;
	while (file)
	{
		if (file->len > topline)
			topline = file->len;
		file = file->next;
	}
	return (topline);
}

char	*addsize(char *data, int len)
{
	char	*newstr;
	char	*spaces;
	int		i;

	if (data[0] == '\0')
		return (ft_strjoin_gnl(data, "\n"));
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
	map = (char **)malloc(sizeof(char *) * (list_size + 1));
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
	t_list	*head;
	int		bline;

	head = file;
	bline = get_bline(file);
	while (file)
	{
		if (bline > file->len)
			file->data = addsize(file->data, bline - file->len);
		file = file->next;
	}
	return (to_matrix(head));
}
