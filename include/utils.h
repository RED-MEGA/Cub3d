/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:08 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/01 20:21:41 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "global.h"
# include "libft.h"

void	perror_x(char *error);
void	ft_free(char **str);
void	ft_error(int status, int code);
void	ft_error_ptr(void *status, int code);
void	ft_error_msg(const char *msg, int code);
bool	compare(char *s1, char *s2);
size_t	ft_matlen(char **matrix);
char	**ft_matrixdup(char **matrix);
t_list	*in(t_list *head, int index);
void	ft_indexing(t_list *list);

#endif