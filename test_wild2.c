/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 11:49:36 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/02 17:16:16 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "expander.h"

int		count_slash(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '/' && i != 0)
			count++;
		i++;
	}
	return (count);
}

char	*getpath(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '*')
		return (ft_strdup("."));
	while (str[i] && str[i] != '*')
		i++;
	while (i > 0 && str[i] != '/')
		i--;
	return (ft_substr(str, 0, i));
}

char	*make_match_str(char *path, struct dirent *match)
{
	char	*str;
	char	*tmp;

	if (!ft_strncmp(path, ".", 2))
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

int	match_str(char *str, char *str2, int i, int j)
{
	if (str2[0] == '.')
		return (0);
	// if (str[0] == '*' && !str[1])
	// 	return (1);
	if (str[i] == '*' && !str[i + 1])
		return (1);
	if ((!str[i] || (str[i] == '*' && !str[i + 1])) && !str2[j])
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

int	add_entry(char *str, int type)
{
	if (type == DT_DIR && str[ft_strlen(str) - 1] == '/')
		return (1);
	else if (type != DT_DIR && str[ft_strlen(str) - 1] == '/')
		return (0);
	return (1);
}

void	searchdir(char *path, char *str, char **arr, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**path_arr;
	char			*tmp;
	int				j;
	// int				k;

	if (!path)
		child_err_msg(NULL, "wildcard1 expansion");
	path_arr = ft_split(str, '/');
	dir = opendir(path);
	if (!path_arr || !dir)
		child_err_msg(NULL, "wildcard2 expansion");
	tmp = ft_strjoin(path, "/");
	// free(path);
	if (!tmp)
		child_err_msg(NULL, "wildcard3 expansion");
	j = count_slash(tmp);
	// k = count_slash(str);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		printf("entry: %s\n", entry->d_name);
		if (entry->d_type == DT_DIR && match_str(path_arr[j], entry->d_name, 0, 0) && path_arr[j + 1])
		{
			path = ft_strjoin(tmp, entry->d_name);
			searchdir(path, str, arr, i);
		}
		else if (match_str(path_arr[j], entry->d_name, 0, 0) && add_entry(str, entry->d_type))
			arr[i++] = make_match_str(tmp, entry);
	}
	free(tmp);
	ft_free_arr(path_arr);
	closedir(dir);
}

void	expand_dir(char ***cmd_array, char *str, int i)
{
	char			*path;
	char			**wildcard_arr;

	if (!ft_strchr(str, '*'))
		return ;
	path = getpath(str);
	if (!path && errno == ENOMEM)
		child_err_msg(NULL, "wildcard expansion");
	else if (!path)
		return ;
	wildcard_arr = ft_calloc(sizeof(char *), 100);
	if (!wildcard_arr)
		child_err_msg(NULL, "wildcard expansion");
	searchdir(path, str, wildcard_arr, 0);
	insert_into_array(wildcard_arr, cmd_array, i);
	// free(path);
	free(str);
	free(wildcard_arr);
}

int	main(int argc, char **argv)
{
	char			*str = ft_strdup(argv[1]);
	char			**arr = ft_arrdup(argv);

	(void)argc;
	expand_dir(&arr, str, 1);
	printf("\n");
	for (size_t i = 0; arr[i]; i++)
		printf("%s\n", arr[i]);
	ft_free_arr(arr);
	exit(0);
}


// gcc -Wall -Wextra -Werror -fsanitize=address -g srcs/init/ft_arrdup.c srcs/executor/expansion/expand_cmd_arrays.c test_wild2.c  srcs/utils.c srcs/error.c libft/libft.a -I incs/ -I libft/incs/ && ./a.out "srcs/exec*/ex*.c"