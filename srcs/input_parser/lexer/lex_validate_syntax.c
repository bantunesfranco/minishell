/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_validate_syntax.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 14:40:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/04 10:25:43 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static bool	is_exit_condition_valid(t_token *temp, int open_brackets)
{
	if (open_brackets != 0)
	{
		lex_error_function(")", 2);
		return (false);
	}
	else if (temp->prev->token_group == WORD)
		return (are_quotes_closed(temp->prev->word));
	return (true);
}

static t_token	*token_order_validation(t_token *head, int *open_brackets, \
										t_par_info *p_info)
{
	t_token	*temp;

	temp = head;
	*open_brackets = 0;
	while (temp->next != NULL)
	{
		if (!is_single_token_valid(temp, open_brackets))
		{
			p_info->syntax_error = 1;
			break ;
		}
		temp = temp->next;
	}
	return (temp);
}

static bool	is_start_condition_valid(t_token *temp)
{
	if (temp->token_group == CONTROL_OPERATOR || \
		temp->type == CLOSE_PAR)
	{
		lex_error_function(temp->word, 1);
		return (false);
	}
	return (true);
}

void	validate_syntax(t_token *head, t_par_info *p_info)
{
	t_token	*temp;
	int		open_brackets;

	temp = head;
	if (!is_start_condition_valid(temp))
		p_info->syntax_error = 1;
	else
	{
		temp = token_order_validation(head, &open_brackets, p_info);
		if (p_info->syntax_error == 1)
			token_order_error(temp, open_brackets);
		else if (!is_exit_condition_valid(temp, open_brackets))
			p_info->syntax_error = 1;
	}
	p_info->error_token = temp;
}
