/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 16:49:42 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/28 13:20:04 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

int	match_str(char *str, char *str2, int i, int j)
{
	if ((!str[i] || (str[i] == '*' && !str[i + 1])) && !str2[j])
		return (1);
	if (str[i] == '*' && !str[i + 1])
		return (1);
	if (!str2[j])
		return (0);
	if (str[i] == str2[j])
		return (match_str(str, str2, i + 1, j + 1));
	if (str[i] == '*')
		while (str2[j])
			if (match_str(str, str2, i + 1, j++))
				return (1);
	return (0);
}

char	*getpath(char *str)
{
	int		i;
	char	*path;

	i = 0;
	while (str[i] != '*')
		i++;
	path = (char *)ft_calloc(sizeof(char), i + 2);
	if (!path)
		err_exit(NULL, "wildcard expander");
	i = 0;
	while (str[i] && (str[i] == '/' || str[i] == '.'))
	{
		path[i] = str[i];
		i++;
	}
	if (i == 0 || str[i - 1] == '/')
	{
		path[i] = '.';
		i++;
	}
	path[i] = '\0';
	return (path);
}

int	count_dirs(char *path)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (path[i])
	{
		if (path[i] && path[i] == '/')
			n++;
		i++;
	}
	return (n);
}

char	**expand_dir(char **match, char *path, char **parr, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	int				nb_dir;
	char			*tmp;

	nb_dir = count_dirs(path);
	dir = opendir(path);
	if (!dir)
		return (NULL);
	if (i == 0)
		i = ft_strlen(path);
}

int	main(void)
{
	char			*str = "../../../../srcs/*i*n*";
	// char			*arr[4096] = {"srcs/incs", "srcs/input", "srcs/lexer", "srcs/main", "srcs/parser", "srcs/ireee", NULL};

	// // expand_dir(str, arr, 0);
	// for (size_t i = 0; arr[i]; i++)
	// {
	// 	if (match_str(str, arr[i], 0, 0) == 1)
	// 		printf("%s: %s\n", arr[i], "POGGERS, its a match");
	// // 	printf("%s\n", arr[i]);
	// }
	printf("%s\n", getpath(str));
	return (0);
}
