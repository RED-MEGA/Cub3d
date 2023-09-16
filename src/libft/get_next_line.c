/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:42:42 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/16 11:02:32 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_slash(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_line(char *stv)
{
	char	*c;
	int		i;

	i = 0;
	if (!stv[i])
		return (NULL);
	if (stv[i] != '\n' && stv[i])
		i = ft_strlen(stv);
	if (ft_check_slash(stv))
		c = malloc(i + 1);
	else
		c = malloc(i + 2);
	if (!c)
		return (NULL);
	i = 0;
	while (stv[i] != '\n' && stv[i])
	{
		c[i] = stv[i];
		i++;
	}
	if (!ft_check_slash(stv))
		c[i++] = '\n';
	c[i] = '\0';
	return (c);
}

static char	*ft_next(char *stv)
{
	int		j;
	int		i;
	char	*st;

	j = 0;
	i = 0;
	while (stv[j] != '\n' && stv[j])
		j++;
	if (!ft_check_slash(stv))
		j++;
	if ((int)ft_strlen(stv) == j)
		return (free(stv), NULL);
	st = malloc(ft_strlen(stv) - j + 1);
	if (!st)
		return (NULL);
	while (stv[j])
		st[i++] = stv[j++];
	st[i] = '\0';
	free(stv);
	stv = NULL;
	return (st);
}

char	*get_next_line(int fd)
{
	int			i;
	char		*buff;
	static char	*stv;
	char		*c;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stv)
		stv = ft_strdup("");
	i = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (ft_check_slash(stv) && i)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			return (free(buff), free(stv), stv = NULL, NULL);
		buff[i] = '\0';
		stv = ft_strjoin(stv, buff);
	}
	free(buff);
	c = ft_line(stv);
	stv = ft_next(stv);
	return (c);
}
