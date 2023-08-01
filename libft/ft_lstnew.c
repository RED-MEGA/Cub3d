/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:14:15 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/01 19:53:38 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *data)
{
	t_list	*newnode;

	newnode = (t_list *)malloc(sizeof(t_list));
	ft_error_ptr(newnode, 1);
	newnode->data = data;
	newnode->next = NULL;
	return (newnode);
}
