/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_parethesis_validation.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 19:43:00 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/11 19:44:31 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_open_par_valid(t_token *temp, int *open_brackets)
{
	(*open_brackets)++;
	if (temp->next->token_group == REDIRECTION || \
		temp->next->token_group == WORD || \
		temp->next->type == OPEN_PAR)
		return (true);
	return (false);
}

static bool	is_close_par_valid(t_token *temp, int *open_brackets)
{
	if (*open_brackets == 0)
		return (false);
	(*open_brackets)--;
	if (temp->next->token_group == WORD || \
		temp->next->type == OPEN_PAR)
		return (false);
	return (true);
}

bool	is_parenthesis_valid(t_token *temp, int *open_brackets)
{
	if (temp->type == OPEN_PAR)
		return (is_open_par_valid(temp, open_brackets));
	return (is_close_par_valid(temp, open_brackets));
}