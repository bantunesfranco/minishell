/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 14:40:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/12 16:51:16 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

/*	similar to the function from creating words*/

static bool	are_quotes_closed(char *word)
{
	size_t	i;
	char	c;

	i = 0;
	while (*(word + i) != '\0')
	{
		if (*(word + i) == '\'' || *(word + i) == '"')
		{
			c = *(word + i);
			i = skip_quotes(word, i);
		}
		if (*(word + i) == '\0')
		{
			lex_error_function(&c, 2);
			return (false);
		}
		i++;
	}
	return (true);
}

/*	checks for error conditions
	first check is when there is only one token, which means ther is aonly a newline ergo, no input
	secondly we check if all brackets were close properly
	third we check if all quotes are closed*/

static bool	is_exit_condition_valid(t_token *temp, int open_brackets)
{
	if (temp->prev == NULL)
		return (true);
	if (open_brackets != 0)
	{
		lex_error_function(")", 2);
		return (false);
	}
	else if (temp->prev->token_group == WORD)
		return (are_quotes_closed(temp->prev->word));
	return (true);
}

/*	runs the error function based on the token order and the token where the error was encountered*/

static void	token_order_error(t_token *temp, int open_brackets)
{
	if (open_brackets == -1)
		lex_error_function(temp->word, 1);
	else if (temp->type == NEW_LINE || temp->next->type == NEW_LINE)
		lex_error_function("newline", 1);
	else
		lex_error_function(temp->next->word, 1);
}

/*	going through the token list and validating the tokens one by one
	if an error occurs we set the error value in the struct to one and return the offending token*/

static t_token	*token_order_validation(t_token *first_token, int *open_brackets, t_parsing_info *p_info)
{
	t_token	*temp;

	temp = first_token;
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

/*	this function validates the syntax based on the generated token list
	first it checks the order of the tokens
	if that encounters an error we use the offending token to print the correct error message
	then we check if everything we opened so far has been propely closed, think parenthesis and quotes
	if that goes wrong we print an apropiate error
	this function sets the error variable in our parser struct to 1 in case of error and leaves it at 0 if the syntax is correct
	we also set out error_token to the token our validation returned
	we only use this in case of an error in the syntax to handle heredocs*/

void	validate_syntax(t_token *first_token, t_parsing_info *p_info)
{
	t_token	*temp;
	int		open_brackets;

	temp = token_order_validation(first_token, &open_brackets, p_info);
	if (p_info->syntax_error == 1)
		token_order_error(temp, open_brackets);
	else if (!is_exit_condition_valid(temp, open_brackets))
		p_info->syntax_error = 1;
	p_info->error_token = temp;
}
