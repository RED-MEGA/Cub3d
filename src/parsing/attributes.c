/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:06:37 by reben-ha          #+#    #+#             */
/*   Updated: 2023/09/13 21:05:27 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	set_direction(char *data, t_img *image)
{
	char	*buff;

	if (image->path != NULL)
		return (perror_x("Direction attribute is Already set")
			, false);
	buff = ft_strtrim(data + 3, " ");
	if (!isvalid_path(buff) || !check_extension(buff, ".png"))
		return (free(buff)
			, perror_x("Invalid direction attribute")
			, false);
	image->path = buff;
	return (true);
}

bool	check_rgbform(char *rgb)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (rgb[++i])
		if (rgb[i] == ',')
			count++;
	if (count != 2)
		return (false);
	i = -1;
	while (rgb[++i])
		if (!ft_isdigit(rgb[i]) && rgb[i] != ',')
			return (false);
	return (true);
}

int	_set_color(char **color, int i, char *to_free)
{
	int	nb;

	nb = ft_atoi(color[i]);
	if (!isrgb(nb))
		return (free(to_free), ft_free(color)
			, ft_error_msg("Wrong RGB range", 1), false);
	return (nb);
}

bool	set_color(char *data, t_color *rgb)
{
	char	*buff;
	char	**color;

	if (rgb->r != FAIL || rgb->g != FAIL || rgb->b != FAIL)
		return (perror_x("Color attribute is Already set"), false);
	buff = ft_strtrim(data + 2, " ");
	if (!check_rgbform(buff))
		return (free(buff), perror_x("Invalid color attribute"), false);
	color = ft_split(buff, ',');
	free(buff);
	rgb->r = _set_color(color, 0, data);
	rgb->g = _set_color(color, 1, data);
	rgb->b = _set_color(color, 2, data);
	ft_free(color);
	return (true);
}
