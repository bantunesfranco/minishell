/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_wild2_copy.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/02 11:49:36 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/03 18:05:22 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"
#include "expander.h"

int	wild_pos(char **arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arr[i])
	{
		if (ft_strchr(arr[i], '*'))
		{
			count = 1;
			break ;
		}
		i++;
	}
	if (count == 0)
		return (0);
	return (i);
}

char	*getpath(char *str)
{
	int		i;

	i = 0;
	if (ft_strchr(str, '/') == ft_strrchr(str, '/'))
		if (!ft_strchr(str, '/') || str[ft_strlen(str) - 1] == '/')
			return (ft_strdup("."));
	while (str[i] && str[i] != '*')
		i++;
	while (i > 0 && str[i] != '/')
		i--;
	return (ft_substr(str, 0, i));
}

char	*make_match_str(char *input, char *path, struct dirent *match)
{
	char	*str;
	char	*tmp;

	if (!ft_strncmp(path, "./", 3))
		str = ft_strdup(match->d_name);
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
	// printf("str: %p\n", str);
	// printf("str2: %p\n", str2);
	// if (str2[0] == '.')
	// 	return (0);
	if (str[0] != '.' && (!ft_strncmp(str2, ".", 2) || !ft_strncmp(str2, "..", 3)))
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

int	add_entry(char *str, int type)
{
	if (type == DT_DIR && str[ft_strlen(str) - 1] == '/')
		return (1);
	else if (type != DT_DIR && str[ft_strlen(str) - 1] == '/')
		return (0);
	return (1);
}

void	searchdir(char *path, char *str, t_list **list, char **arr)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*tmp;

	if (!path)
		child_err_msg(NULL, "wildcard expansion");
	dir = opendir(path);
	if (!dir)
		child_err_msg(NULL, "wildcard 4444 expansion");
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		child_err_msg(NULL, "wildcard expansion");
	while (*arr)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		// printf("entry: %s\n", ent->d_name);
		if (ent->d_type == DT_DIR && arr[1] && match(*arr, ent->d_name, 0, 0))
		{
			free(path);
			path = ft_strjoin(tmp, ent->d_name);
			searchdir(path, str, list, &arr[1]);
		}
		else if (match(*arr, ent->d_name, 0, 0) && !arr[1] && add_entry(str, ent->d_type))
			ft_lstadd_back(list, ft_lstnew(make_match_str(str, tmp, ent)));
	}
	free(tmp);
	closedir(dir);
}

char	**ft_lst_to_arr(t_list **list)
{
	int		len;
	int		i;
	char	**arr;
	t_list	*head;

	len = ft_lstsize(*list);
	arr = ft_calloc(sizeof(char *), len + 1);
	head = *list;
	i = 0;
	while (head)
	{
		arr[i] = head->content;
		head = head->next;
		i++;
	}
	free(list);
	return (arr);
}

void	expand_dir(char ***cmd_array, char *str, int i)
{
	char			*path;
	char			**path_arr;
	t_list			**list;

	if (!ft_strchr(str, '*'))
		return ;
	list = ft_calloc(sizeof(t_list *), 1);
	path_arr = ft_split(str, '/');
	path = getpath(str);
	if ((!path || !list || !path_arr) && errno == ENOMEM)
		child_err_msg(NULL, "wildcard expansion");
	else if (!path)
		return ;
	searchdir(path, str, list, &path_arr[wild_pos(path_arr)]);
	ft_free_arr(path_arr);
	path_arr = ft_lst_to_arr(list);
	if (!path_arr)
		child_err_msg(NULL, "wildcard expansion");
	insert_into_array(path_arr, cmd_array, i);
	// free(path);
	free(str);
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