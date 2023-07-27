/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:50:06 by reben-ha          #+#    #+#             */
/*   Updated: 2023/07/27 14:46:48 by reben-ha         ###   ########.fr       */
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

# define ERROR  "\033[31;1mError :\033[0m "
# define FAIL -1
# define SUCCESS 0

# define ERRMALLOC "Cannot allocate memory"
# define ERRFORK "Failed to fork process"
# define ERRPERMISSION "Permission denied"
# define ERRINVALID "Invalid argument"
# define ERRFILE "Invalid file"

# define C_EAT "\e[1;35m"
# define C_SLEEP "\e[1;30m"
# define C_THINK "\e[1;33m"
# define C_DEATH "\033[1;31m"
# define C_RESET "\e[0m"

typedef struct s_list
{
	char			*data;
	int				index;
	struct s_list	*next;
}					t_list;


typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

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

#endif