/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_wildcards.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 11:49:36 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/04 19:04:00 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "expander.h"

char	*make_match_str(char *input, char *path, struct dirent *match)
{
	char	*str;
	char	*tmp;

	if (!ft_strncmp(path, "./", 2))
		str = ft_strjoin(path + 2, match->d_name);
	else
		str = ft_strjoin(path, match->d_name);
	if (str && match->d_type == DT_DIR && input[ft_strlen(input) - 1] == '/')
	{
		tmp = str;
		str = ft_strjoin(str, "/");
		free(tmp);
	}
	if (!str)
		child_err_msg(NULL, "wildcard expansion");
	return (str);
}

int	match(char *str, char *str2, int i, int j)
{
	if (str[0] != '.' && str2[0] == '.')
		return (0);
	if (str[i] == '*' && !str[i + 1])
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

void	searchdir(char *path, char *str, t_list **list, char **arr)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	setup_dir_search(&dir, &tmp, path);
	while (*arr)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if (ent->d_type == DT_DIR && arr[1] && match(*arr, ent->d_name, 0, 0))
		{
			searchdir(ft_strjoin(tmp, ent->d_name), str, list, &arr[1]);
		}
		else if (match(*arr, ent->d_name, 0, 0) \
		&& !arr[1] && add_entry(str, ent->d_type))
		{
			ft_lstadd_back(list, ft_lstnew(make_match_str(str, tmp, ent)));
			if (errno == ENOMEM)
				child_err_msg(NULL, "wildcard expansion");
		}
	}
	free(path);
	free(tmp);
	closedir(dir);
}

char	**ft_lst_to_arr(t_list **list)
{
	int		len;
	int		i;
	char	**arr;
	t_list	*head;
	t_list	*tmp;

	len = ft_lstsize(*list);
	arr = ft_calloc(sizeof(char *), len + 1);
	head = *list;
	i = 0;
	while (head)
	{
		arr[i] = head->content;
		tmp = head;
		head = head->next;
		free(tmp);
		i++;
	}
	free(list);
	return (arr);
}

int	expand_wildcards(char ***cmd_array, char *str, int i)
{
	char			*path;
	char			**path_arr;
	t_list			**list;

	if (!ft_strchr(str, '*'))
		return (i + 1);
	list = ft_calloc(sizeof(t_list *), 1);
	path_arr = ft_split(str, '/');
	path = getpath(str);
	if ((!path || !list || !path_arr) && errno == ENOMEM)
		child_err_msg(NULL, "wildcard expansion");
	else if (!path)
		return (i + 1);
	searchdir(path, str, list, &path_arr[wild_pos(path_arr)]);
	ft_free_arr(path_arr);
	path_arr = ft_lst_to_arr(list);
	if (!path_arr)
		child_err_msg(NULL, "wildcard expansion");
	if (*path_arr == NULL)
	// {
		return (free(path_arr), i + 1);
	// }
	insert_into_array(path_arr, cmd_array, i);
	i = i + ft_arrlen(path_arr);
	free(path_arr);
	free(str);
	return (i);
}

// int	main(int argc, char **argv)
// {
// 	char			*str = ft_strdup(argv[1]);
// 	char			**arr = ft_arrdup(argv);

// 	(void)argc;
// 	expand_dir(&arr, str, 1);
// 	printf("\n");
// 	for (size_t i = 0; arr[i]; i++)
// 		printf("%s\n", arr[i]);
// 	ft_free_arr(arr);
// 	exit(0);
// }
