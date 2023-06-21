/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_redirections.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 07:04:39 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/21 11:10:04 by jmolenaa      ########   odam.nl         */
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
	word = expand_environment_vars(*name, gen, 0, &head);
	split_word = word_splitting(word, head);
	if (ft_arrlen(split_word) != 1)
	{
		*name = save;
		free(word);
		ft_free_arr(split_word);
		free_quote_list(head);
		return (false);
	}
	quote_removal(split_word, head);
	free(word);
	*name = *split_word;
	free(split_word);
	free(save);
	free_quote_list(head);
	return (true);
}

// void	expand_heredoc(char *str, char *delim)
// {
// 	if (ft_strchr(delim, '\'') || ftsrcg(delim, '"'))
// 		return (str);
// 	str = expand(str heredoc 1);
// 	return (str);
// }

// void	expand_delim(char *delim)
// {
// 	delim = quote_remove_delim( loop till quotes, memmove then loop till next same quote and memmove adn go on looping)
// }
