/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 15:07:27 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/20 08:42:20 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "libft.h"
#include "parsing.h"

void	lks(void)
{
	system("leaks -q expansion_test");
}

void	print_quotes(t_quote_mark *head)
{
	while (head != NULL)
	{
		printf("%zu index %zu\n", head->array_index, head->word_index);
		head = head->next;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	t_gen			gen;
	char			**start_env;
	char			*word;
	t_quote_mark	*head;
	char	**split_vars;
	// int		i;
	atexit(lks);
	head = NULL;
	printf("\n\n\nNEW THINGY\n\n\n");
	// i = 0;
	start_env = ft_arrdup(envp);
	gen.env = env_init(start_env);
	gen.status = 0;
	word = expand_environment_vars(ft_strdup(argv[1]), &gen, 0, &head);
	// print_quotes(head);
	printf("%s\n\n", word);
	// split_vars = split_word(word);
	split_vars = word_splitting(word, head);
	// free(word);
	// printf("%p\n")
	// printf("printing array\n");
	// print_array(split_vars);
	// printf("done\n\n");
	quote_removal(split_vars, head);
	free_quote_list(head);
	//realloc of cmd array
	printf("printing array\n");
	print_array(split_vars);
	printf("done\n\n");
	// while (*(split_vars + i) != NULL)
	// {
	// 	quote_removal(*(split_vars + i));
	// 	i++;
	// }
	ft_free_arr(gen.env);
	ft_free_arr(split_vars);
	free(word);
}

// awe=Aassss

// lo$awe$awe

// start = 2
// strlen = 6
// return_value = 2 + 6 -1 = 7

// loAassss$awe

