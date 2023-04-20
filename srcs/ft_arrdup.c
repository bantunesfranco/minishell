/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arrdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 11:26:34 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/20 12:13:54 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i++;
	return (i);
}

char	**ft_arrdup(char **arr)
{
	char	**newarr;
	int		i;
	int		size;

	size = get_arr_size(arr);
	if (size == 0)
		return (NULL);
	i = 0;
	if (!arr)
		return (NULL);
	newarr = ft_calloc(size + 1, sizeof(char *));
	if (!newarr)
		return (NULL);
	while (arr[i])
	{
		newarr[i] = ft_strdup(arr[i]);
		if (!newarr[i])
			return (ft_free_arr(newarr), NULL);
		i++;
	}
	newarr[i] = NULL;
	return (newarr);
}
