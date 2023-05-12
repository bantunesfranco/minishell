/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_token_validation.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 19:41:08 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/11 19:44:58 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_control_operator_valid(t_token *temp, int *open_brackets)
{
	(void)open_brackets;
	if (temp->next->token_group == REDIRECTION || \
		temp->next->token_group == WORD || \
		temp->next->type == OPEN_PAR)
		return (true);
	return (false);
}

static bool	is_redirection_valid(t_token *temp, int *open_brackets)
{
	(void)open_brackets;
	if (temp->next->token_group == WORD)
		return (true);
	return (false);
}

static bool	is_whitespace_valid(t_token *temp, int *open_brackets)
{
	(void)open_brackets;
	if (temp->next == NULL)
		return (true);
	return (false);
}

static bool	is_word_valid(t_token *temp, int *open_brackets)
{
	(void)open_brackets;
	if (temp->next->type == OPEN_PAR)
		return (false);
	return (true);
}

bool	is_token_valid(t_token *temp, int *open_brackets)
{
	bool	(*is_not_valid[5])(t_token *, int *);

	is_not_valid[0] = is_control_operator_valid;
	is_not_valid[1] = is_parenthesis_valid;
	is_not_valid[2] = is_redirection_valid;
	is_not_valid[3] = is_whitespace_valid;
	is_not_valid[4] = is_word_valid;
	return (is_not_valid[temp->token_group](temp, open_brackets));
}
