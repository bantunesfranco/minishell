/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_redirections.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 07:04:39 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 22:04:41 by jmolenaa      ########   odam.nl         */
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
	char			*save_word;

	head = NULL;
	save_word = ft_strdup(*name);
	if (save_word == NULL)
		err_msg(NULL, "expander");
	word = expand_env(*name, gen, 0, &head);
	split_word = word_splitting(word, head);
	free(word);
	quote_removal(split_word, head);
	free_quote_list(head);
	if (ft_arrlen(split_word) == 1)
	// {
		expand_wildcards(&split_word, *split_word, 0);
	// 	*name = save_word;
	// 	ft_free_arr(split_word);
	// 	return (false);
	// }
	if (ft_arrlen(split_word) != 1)
	{
		*name = save_word;
		ft_free_arr(split_word);
		return (false);
	}
	
	*name = *split_word;
	free(split_word);
	free(save_word);
	return (true);
}
