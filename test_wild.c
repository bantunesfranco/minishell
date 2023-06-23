/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 16:49:42 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/23 08:37:05 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "libft.h"

int	main(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*str = "*i*.c";
	// char			*arr[];
	// int				i;

	// i = 0;
	dir = opendir("./srcs/");
	while ((entry = readdir(dir)) != NULL)
	{
		// printf("|%u|\n", entry->d_type);
		if (strstr(entry->d_name, ft_strchr(str, '*') + 1))
			printf("|%s|\n", entry->d_name);
	}
	closedir(dir);
	return (0);
}
