/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 16:49:42 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/26 20:40:20 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include "minishell.h"


int	match_str(char *str, char *str2)
{
	int	i;

	i = 0;
	if (str[0] == '*' && str[1] == '/')
		return (1);
	if (!ft_strncmp(str2, ".", 2) || !ft_strncmp(str2, "..", 3))
		return (0);
	while (str[i] && str2[i] && str[i + 1] != '*')
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



char	*getpath(char *str, int *f)
{
	int		i;
	char	*path;

	i = 0;
	if (str[0] == '*' && (str[1] == '/' || str[1] == '\0'))
	{
		if (str[1] == '/')
			*f = 1;
		return (getcwd(NULL, 0));
	}
	while (str[i] != '*')
		i++;
	while (i > 0 && str[i] != '/')
		i--;
	if (str[i + 1] == '/')
		*f = 1;
	path = ft_substr(str, 0, i);
	return (path);
}

void	expand_dir(char *str, char *arr[4096], int i)
{
	DIR				*dir;
	struct dirent	*entry;
	int				folder;
	char			*path;
	char			*match;

	folder = 0;
	path = getpath(str, &folder);
	if (!path)
	{
		err_msg(NULL, "wildcard");
		exit(errno);
	}
	// printf("%s\n", path);
	dir = opendir(path);
	while ((entry = readdir(dir)) != NULL)
	{
		match = ft_strchr(str + ft_strlen(path), '/');
		// printf("%s\n", match);
		if (match_str(match + 1, entry->d_name))
		{
			arr[i] = entry->d_name;
			i++;
		}
	}
	arr[i] = NULL;
	free(path);
	// closedir(dir);
	// while (str[j] != '*')
	// 	j++;
	// if (str[j])
	// 	expand_dir(str + j, arr, i);
}

int	main(void)
{
	char			*str = "srcs/i*";
	char			*arr[4096];

	expand_dir(str, arr, 0);
	for (size_t i = 0; arr[i]; i++)
	{
		printf("%s\n", arr[i]);
	}
	return (0);
}
