/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:15:29 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/26 00:03:11 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t nulb)
{
	size_t	i;
	char	*destx;
	char	*srcx;

	destx = (char *)dest;
	srcx = (char *)src;
	i = 0;
	if (destx == NULL && srcx == NULL)
		return (NULL);
	while (i < nulb)
	{
		destx[i] = srcx[i];
		i++;
	}
	return (destx);
}
