/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 16:49:42 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/29 14:39:14 by bfranco       ########   odam.nl         */
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
	while (str[i] && str[i] != '*')
		i++;
	path = (char *)ft_calloc(sizeof(char), i + 2);
	if (!path)
		err_msg(NULL, "wildcard expander");
	i = 0;
	while (str[i] && (str[i] == '/' || str[i] == '.'))
	{
		path[i] = str[i];
		i++;
	}
	if (i == 0)// || str[i - 1] == '/')
	{
		path[i] = '.';
		// i++;
	}
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

int	ft_strequal(char *s1, char *s2)
{
	int	len;

	len = ft_strlen(s1) + 1;
	if (ft_strncmp(s1, s2, len) != 0)
		return (0);
	return (1);
}

char	**expand_dir(char *match, char *path, char **parr, int i)
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
		i = ft_strlen(path) - 1;
	else
		i = 0;
	while (match[i] && match[i] != '/')
		i++;
	while (parr[nb_dir] && dir)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		tmp = ft_strjoin("/", entry->d_name);
		if (tmp)
			tmp = ft_strjoin(path, tmp);
		if (!tmp)
			err_msg(NULL, "wildcard expansion");
		if ((ft_strequal(parr[nb_dir], entry->d_name) || match_str(match, entry->d_name, i + 1, 0)) && !ft_strequal(".", entry->d_name) \
		&& !ft_strequal("..", entry->d_name) && !ft_strequal(parr[nb_dir], match + i + 1))
			expand_dir(match, tmp, parr, i + 1);
		else if (match_str(match, entry->d_name, i + 1, 0) && (!ft_strequal(".", entry->d_name) && !ft_strequal("..", entry->d_name)))
			printf("%s\n", entry->d_name);
		free(tmp);
	}
	return (NULL);
}

int	main(void)
{
	char			*str = "srcs/i*";
	// char			*arr[4096] = {"srcs/incs", "srcs/input", "srcs/lexer", "srcs/main", "srcs/parser", "srcs/ireee", NULL};

	expand_dir(str, getpath(str), ft_split(str, '/'), 0);
	// for (size_t i = 0; arr[i]; i++)
	// {
	// 	if (match_str(str, arr[i], 0, 0) == 1)
	// 		printf("%s: %s\n", arr[i], "POGGERS, its a match");
	// // 	printf("%s\n", arr[i]);
	// }
	// printf("%s\n", getpath(str));
	return (0);
}
