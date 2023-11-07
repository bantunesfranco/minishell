/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_token_validation.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 19:41:08 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/11/01 08:08:45 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

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

bool	is_single_token_valid(t_token *temp, int *open_brackets)
{
	t_is_order_valid	token_order_validation[5];

	token_order_validation[0] = is_control_operator_valid;
	token_order_validation[1] = is_parenthesis_valid;
	token_order_validation[2] = is_redirection_valid;
	token_order_validation[3] = is_whitespace_valid;
	token_order_validation[4] = is_word_valid;
	return (token_order_validation[temp->token_group](temp, open_brackets));
}
