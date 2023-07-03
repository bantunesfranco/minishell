/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 11:54:44 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/03 12:36:15 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "expander.h"

int	match(char *str, char *str2, int i, int j)
{
	if (str2[0] == '.')
		return (0);
	if (str[i] == '*' && (!str[i + 1] || str[i + 1] == '/'))
		return (1);
	if ((!str[i] || (str[i] == '*' && !str[i + 1])) && !str2[j])
		return (1);
	if (!str2[j])
		return (0);
	if (str[i] == str2[j])
		return (match(str, str2, i + 1, j + 1));
	if (str[i] == '*')
		while (str2[j])
			if (match(str, str2, i + 1, j++))
				return (1);
	return (0);
}

char	*make_match_str(char *path, struct dirent *match)
{
	char	*str;
	char	*tmp;

	if (!ft_strncmp(path, "./", 3))
		str = ft_strdup(match->d_name);
	else
		str = ft_strjoin(path, match->d_name);
	if (str && match->d_type == DT_DIR && str[ft_strlen(str) - 1] == '/')
	{
		tmp = str;
		str = ft_strjoin(str, "/");
		free(tmp);
	}
	if (!str)
		child_err_msg(NULL, "wildcard expansion");
	return (str);
}

DIR	*dir_setup(char ***p, char **tmp, char *path, char *str)
{
	DIR				*dir;

	if (!path)
		child_err_msg(NULL, "wildcard1 expansion");
	*p = ft_split(str, '/');
	dir = opendir(path);
	if (!*p || !dir)
		child_err_msg(NULL, "wildcard2 expansion");
	*tmp = ft_strjoin(path, "/");
	// free(path);
	if (!*tmp)
		child_err_msg(NULL, "wildcard3 expansion");
	return (dir);
}

void	searchdir(char *path, char *str, char **arr, int i)
{
	DIR				*dir;
	struct dirent	*ent;
	char			**p;
	char			*tmp;
	int				j;

	dir = dir_setup(&p, &tmp, path, str);
	j = count_slash(path);
	while (1)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		printf("ent: %s\n", ent->d_name);
		if (ent->d_type == DT_DIR && match(p[j], ent->d_name, 0, 0) && p[j + 1])
		{
			path = ft_strjoin(tmp, ent->d_name);
			searchdir(path, str, arr, i);
		}
		else if (match(p[j], ent->d_name, 0, 0) && add_entry(str, ent->d_type))
			arr[i++] = make_match_str(tmp, ent);
	}
	free(tmp);
	ft_free_arr(p);
	closedir(dir);
}
