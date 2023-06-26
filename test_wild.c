/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 16:49:42 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/26 10:52:43 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "libft.h"


int	match_str(char *str, char *str2)
{
	int	i;

	i = 0;
	if (str[0] == '*' && str[1] == '/')
		return (1);
	while (str[i] && str2[i] && str[i] != '*')
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	if (i == 0)
	{
		if (ft_strnstr(str2, str + 1, ft_strlen(str2)) == NULL)
			return (0);
		return (1);
	}
	if ((str[i] == '\0' || str2[i] == '\0') && str[i] != str2[i])
		return (0);
	return (1);
}

void	expand_dir(char *str, char *arr[4096], int i)
{
	// DIR				*dir;
	// struct dirent	*entry;
	// int				j;
	// j = 0;
	// dir = opendir("./srcs/");
	// while ((entry = readdir(dir)) != NULL)
	// {
	// 	if (match_str(str, entry->d_name))
	// 	{
	// 		arr[i] = entry->d_name;
	// 		i++;
	// 	}
	// }
	// closedir(dir);
	// arr[i] = NULL;
	// while (str[j] != '*')
	// 	j++;
	// if (str[j])
	// 	expand_dir(str + j, arr, i);
}

int	main(void)
{
	char			*str = "*.c";
	char			*arr[4096];

	expand_dir(str, arr, 0);
	// for (size_t i = 0; arr[i]; i++)
	// {
	// 	printf("%s\n", arr[i]);
	// }
	return (0);
}
