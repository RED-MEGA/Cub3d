/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:17:22 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/04 14:17:56 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	ft_error(int status, int code)
{
	if (status == FAIL)
		return (perror(ERROR), exit(code));
}

void	ft_error_ptr(void *status, int code)
{
	if (status == NULL)
		return (perror(ERROR), exit(code));
}

void	ft_error_msg(const char *msg, int code)
{
	if (msg != NULL)
		return (perror_x(msg), exit(code));
}

void	perror_x(const char *error)
{
	ft_putstr_fd(ERROR, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
