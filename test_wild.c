/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 16:49:42 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/22 17:06:27 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

int	main(void)
{
	DIR	*dir;
	struct dirent	*entry;
	
	dir = opendir("./srcs/");
	while ((entry = readdir(dir)) != NULL)
	{
		printf("|%s|\t", entry->d_name);
		printf("|%u|\n", entry->d_type);
	}
	closedir(dir);
	return (0);
}
