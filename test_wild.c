/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/22 16:49:42 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/30 21:31:57 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "expander.h"

int	match_str(char *str, char *str2, int i, int j)
{
	if (str2[0] == '.')
		return (0);
	if (str[0] == '*' && str[1] == '\0')
		return (1);
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

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	while (str[i] && str[i] == '/')
		i++;
	if (str[i] == '/' && str[i + 1] != '\0')
		return (NULL);
	if (str[ft_strlen(str) - 1] == '/')
	{
		str[ft_strlen(str) - 1] = '\0';
		*f = 1;
	}
	if (str[0] == '*' && (str[1] == '/' || str[1] == '\0'))
		return (ft_strdup("."));
	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	while (i > 0 && str[i - 1] != '/')
		i--;
	return (ft_substr(str, 0, i));
}

char	*make_match_str(char *path, char *match)
{
	char	*str;

	if (!ft_strncmp(path, ".", 2))
		str = ft_strdup(match);
	else
		str = ft_strjoin(path, match);
	if (!str)
		child_err_msg(NULL, "wildcard expansion");
	return (str);
}

void	searchdir(char *path, char *str, char **arr, int f)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	i = 0;
	dir = opendir(path);
	while (dir)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (entry->d_type == DT_DIR && f == 1 \
		&& match_str(str, entry->d_name, ft_strlen(path) , 0))
			arr[i++] = make_match_str(path, entry->d_name);
		else if (f == 0 && match_str(str, entry->d_name, ft_strlen(path), 0))
			arr[i++] = make_match_str(path, entry->d_name);
	}
	if (dir)
		closedir(dir);
}

void	expand_dir(char ***cmd_array, char *str, int i)
{
	int				folder;
	char			*path;
	char			**wildcard_arr;

	if (!ft_strchr(str, '*'))
		return ;
	folder = 0;
	path = getpath(str, &folder);
	if (!path && errno == ENOMEM)
		child_err_msg(NULL, "wildcard expansion");
	else if (!path)
		return ;
	wildcard_arr = ft_calloc(sizeof(char *), 100);
	if (!wildcard_arr)
		child_err_msg(NULL, "wildcard expansion");
	searchdir(path, str, wildcard_arr, folder);
	insert_into_array(wildcard_arr, cmd_array, i);
	free(path);
	free(str);
	free(wildcard_arr);
}

int	main(int argc, char **argv)
{
	char			*str = ft_strdup(argv[1]);
	char			**arr = ft_arrdup(argv);

	(void)argc;
	expand_dir(&arr, str, 1);
	for (size_t i = 0; arr[i]; i++)
		printf("%s\n", arr[i]);
	ft_free_arr(arr);
}
