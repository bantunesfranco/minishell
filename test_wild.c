/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 16:49:42 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/30 14:38:10 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

int	match_str(char *str, char *str2, int i, int j)
{
	if (!ft_strncmp(str2, ".", 2) || !ft_strncmp(str2, "..", 3))
		return (0);
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

char	*getpath(char *str, int *f)
{
	int		i;
	char	*path;

	i = 0;
	if (str[ft_strlen(str) - 1] == '/')
	{
		str[ft_strlen(str) - 1] = '\0';
		*f = 1;
	}
	if (str[0] == '*' && (str[1] == '/' || str[1] == '\0'))
		return (ft_strdup("."));
	while (str[i] != '*')
		i++;
	while (i > 0 && str[i] != '/')
		i--;
	path = ft_substr(str, 0, i);
	return (path);
}

void	expand_dir(char *str, char **arr, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	int				folder;
	char			*path;

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
		if (match_str(str, entry->d_name, ft_strlen(path) + 1, 0) \
		&& folder == 1 && entry->d_type == DT_DIR)
			arr[i++] = ft_strdup(entry->d_name);
		else if (match_str(str, entry->d_name, ft_strlen(path) + 1, 0) \
		&& folder == 0)
			arr[i++] = ft_strdup(entry->d_name);
		else
			continue ;
	}
	free(path);
	if (dir)
		closedir(dir);
}

int	main(void)
{
	char			*str = ft_strdup("*");
	char			**arr = ft_calloc(sizeof(char *), 200);
	// int				i;

	// i = -1;
	expand_dir(str, arr, 0);
	for (size_t i = 0; arr[i]; i++)
		printf("%s\n", arr[i]);
	ft_free_arr(arr);
	free(str);
	return (0);
}
