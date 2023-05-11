/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 14:40:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/11 18:07:25 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

bool	is_control_operator_valid(t_token *temp, int *open_brackets)
{
	(void)temp;
	(void)open_brackets;
	printf("hi\n");
	return (false);
}`

bool	is_parenthesis_valid(t_token *temp, int *open_brackets)
{
	(void)temp;
	(void)open_brackets;
	printf("hi\n");
	return (false);
}

bool	is_redirection_valid(t_token *temp, int *open_brackets)
{
	(void)temp;
	(void)open_brackets;
	printf("hi\n");
	return (false);
}

bool	is_whitespace_valid(t_token *temp, int *open_brackets)
{
	(void)temp;
	(void)open_brackets;
	printf("hi\n");
	return (false);
}

bool	is_word_valid(t_token *temp, int *open_brackets)
{
	(void)temp;
	(void)open_brackets;
	printf("hi\n");
	return (false);
}

bool	token_is_not_valid(t_token *temp, int *open_brackets)
{
	bool	(*is_not_valid[5])(t_token *, int *);

	is_not_valid[0] = is_control_operator_valid;
	is_not_valid[1] = is_parenthesis_valid;
	is_not_valid[2] = is_redirection_valid;
	is_not_valid[3] = is_whitespace_valid;
	is_not_valid[4] = is_word_valid;
	return (is_not_valid[temp->token_group](temp, open_brackets));
}

void	analyze_syntax(t_token	*first_token, t_parsing_info *p_info)
{
	t_token	*temp;
	int		open_brackets;

	temp = first_token;
	while (temp != NULL)
	{
		if (token_is_not_valid(temp, &open_brackets))
		{
			p_info->syntax_error = 1;
			break ;
		}
		temp = temp->next;
	}
}

