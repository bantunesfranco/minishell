/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 15:07:27 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/08 18:45:44 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "libft.h"

void	lks(void)
{
	system("leaks expansion_test");
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	t_gen	gen;
	char	**start_env;
	char	*word;
	char	**split_vars;

	// atexit(lks);
	start_env = ft_arrdup(envp);
	gen.env = env_init(start_env);
	gen.status = 0;
	word = expand_environment_vars(ft_strdup(argv[1]), &gen);
	printf("%s\n\n", word);
	split_vars = split_words(word);
	ft_free_arr(gen.env);
	free(word);
}