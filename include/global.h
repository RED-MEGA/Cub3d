/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:06 by reben-ha          #+#    #+#             */
/*   Updated: 2023/08/02 17:02:44 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include "MLX42/MLX42.h"

# define ERROR  "\033[31;1mError :\033[0m "
# define FAIL -1
# define SUCCESS 0

# define ERRMALLOC "Cannot allocate memory"
# define ERRFORK "Failed to fork process"
# define ERRPERMISSION "Permission denied"
# define ERRINVALID "Invalid argument"
# define ERRFILE "Invalid file"
# define ERREMPTY "Empty file"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# define HEIGHT 2880
# define WIDTH 5120

typedef struct s_list
{
	char			*data;
	int				len;
	int				index;
	struct s_list	*next;
}	t_list;

typedef struct s_pos
{
	int x;
	int y;
}	t_pos;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_info
{
	t_color		F;
	t_color		C;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		**map;
}	t_info;

typedef struct s_global
{
	t_info		*info;
	mlx_t		*mlx;
	mlx_image_t	*window_img;
}	t_global;


#endif