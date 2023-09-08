/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:11:09 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/08 20:12:12 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

bool	compare(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (false);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}
