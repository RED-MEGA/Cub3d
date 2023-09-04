/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:22:41 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/04 14:17:56 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

size_t	ft_matlen(char **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

char	**ft_matrixdup(char **matrix)
{
	char	**new_matrix;
	int		i;

	if (!matrix)
		return (NULL);
	new_matrix = (char **)malloc(ft_matlen(matrix) * sizeof(char *) + 1);
	ft_error_ptr(new_matrix, 1);
	i = -1;
	while (matrix[++i])
		new_matrix[i] = ft_strdup(matrix[i]);
	new_matrix[i] = NULL;
	return (new_matrix);
}
