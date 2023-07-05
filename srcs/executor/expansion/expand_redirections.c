/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_redirections.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 07:04:39 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 19:04:24 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"

bool	expand_redirect(char **name, t_gen *gen)
{
	t_quote_mark	*head;
	char			*word;
	char			**split_word;
	char			*save;

	head = NULL;
	save = ft_strdup(*name);
	if (save == NULL)
		err_msg(NULL, "expander");
	word = expand_env(*name, gen, 0, &head);
	split_word = word_splitting(word, head);
	free(word);
	if (ft_arrlen(split_word) != 1)
	{
		*name = save;
		ft_free_arr(split_word);
		free_quote_list(head);
		return (false);
	}
	quote_removal(split_word, head);
	// expand_wildcards(&split_word, *split_word, 0);
	// if (ft_arrlen(split_word) != 1)
	// {
	// 	*name = save;
	// 	ft_free_arr(split_word);
	// 	free_quote_list(head);
	// 	return (false);
	// }
	*name = *split_word;
	free(split_word);
	free(save);
	free_quote_list(head);
	return (true);
}
