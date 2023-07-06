/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_redirections.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 07:04:39 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/06 09:45:09 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"

static bool	expand_name(char **name, t_gen *gen)
{
	t_quote_mark	*head;
	char			*word;
	char			**split_word;

	head = NULL;
	word = expand_env(*name, gen, 0, &head);
	split_word = word_splitting(word, head);
	quote_removal(split_word, head);
	free(word);
	free_quote_list(head);
	if (ft_arrlen(split_word) == 1)
		expand_wildcards(&split_word, *split_word, 0);
	if (ft_arrlen(split_word) != 1)
	{
		ft_free_arr(split_word);
		return (false);
	}
	*name = *split_word;
	free(split_word);
	return (true);
}

bool	expand_redirect(char **name, t_gen *gen)
{
	char			*save_word;

	save_word = ft_strdup(*name);
	if (save_word == NULL)
		err_msg(NULL, "expander");
	if (expand_name(name, gen) == true)
	{
		free(save_word);
	}
	else
	{
		*name = save_word;
		return (false);
	}
	return (true);
}
