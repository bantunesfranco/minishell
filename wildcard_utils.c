/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 11:54:44 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/03 19:07:23 by bfranco       ########   odam.nl         */
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

int	add_entry(char *str, int type)
{
	if (type == DT_DIR && str[ft_strlen(str) - 1] == '/')
		return (1);
	else if (type != DT_DIR && str[ft_strlen(str) - 1] == '/')
		return (0);
	return (1);
}
