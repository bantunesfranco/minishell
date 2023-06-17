/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 15:07:27 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/17 14:07:14 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "libft.h"
#include "parsing.h"

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
	// char	**split_vars;
	// int		i;

	// atexit(lks);
	// i = 0;
	start_env = ft_arrdup(envp);
	gen.env = env_init(start_env);
	gen.status = 0;
	word = expand_environment_vars(ft_strdup(argv[1]), &gen, 0);
	printf("%s\n\n", word);
	// split_vars = split_word("a a\"lol\"\'a a \'\"bro\" ha");
	// split_vars = split_word(word);
	// printf("printing array\n");
	// print_array(split_vars);
	// printf("done\n");
	// while (*(split_vars + i) != NULL)
	// {
	// 	quote_removal(*(split_vars + i));
	// 	i++;
	// }
	ft_free_arr(gen.env);
	free(word);
}

// awe=Aassss

// lo$awe$awe

// start = 2
// strlen = 6
// return_value = 2 + 6 -1 = 7

// loAassss$awe

