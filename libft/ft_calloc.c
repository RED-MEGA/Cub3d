/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:18:11 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/26 11:02:28 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	ft_error_ptr(result, 1);
	ft_bzero(result, (count * size));
	return (result);
}
