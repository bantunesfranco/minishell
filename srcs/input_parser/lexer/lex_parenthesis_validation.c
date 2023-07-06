/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_parenthesis_validation.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 19:43:00 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/07/04 18:46:46 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_structs.h"

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
	(*open_brackets)--;
	if (*open_brackets == -1)
		return (false);
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
