/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 15:07:27 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/02 08:21:50 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "libft.h"

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

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	t_gen	gen;
	char	**start_env;

	start_env = ft_arrdup(envp);
	gen.env = env_init(start_env);
	expand_environment_vars(argv[1], &gen);
}