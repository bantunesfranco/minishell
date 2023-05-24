/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_parenthesis_validation.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 19:43:00 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/24 16:31:17 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_structs.h"

/*	an open parenthesis has to be followed by a redirection a word or an open parenthesis
	it cannot be followed by a close parenthesis another control operator or a newline
	i also increase my count of open parenthesis*/

static bool	is_open_par_valid(t_token *temp, int *open_brackets)
{
	(*open_brackets)++;
	if (temp->next->token_group == REDIRECTION || \
		temp->next->token_group == WORD || \
		temp->next->type == OPEN_PAR)
		return (true);
	return (false);
}

/*	a close parenthesis has to be followed by a redirection a control operator a close parenthesis or a newline
	it cannot be followed by an open parenthesis or a word
	i also check if I'm not closing parethesis that weren't opened*/

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