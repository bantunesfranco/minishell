/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 12:49:27 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/11/15 11:47:04 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing_structs.h"

void	err_msg(char *msg, char *msg2)
{
	write(2, "minishell: ", 11);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
	}
	if (errno == 127)
	{
		write(2, msg2, ft_strlen(msg2));
		write(2, ": command not found\n", 20);
	}
	else
	{
		if (msg2 && *msg2 == '\0')
			write(2, ": ", 2);
		perror(msg2);
	}
	if (errno == ENOMEM)
	{
		rl_clear_history();
		set_echoctl();
		exit(errno);
	}
}

void	child_err_msg(char *msg, char *msg2)
{
	write(2, "minishell: ", 11);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
	}
	if (errno == 127)
	{
		write(2, msg2, ft_strlen(msg2));
		write(2, ": command not found\n", 20);
	}
	else
		perror(msg2);
	_exit(errno);
}

void	built_err_msg(char *msg, char *msg2, char *msg3)
{
	write(2, "minishell: ", 11);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, ": ", 2);
	}
	if (msg2)
	{
		write(2, "`", 1);
		write(2, msg2, ft_strlen(msg2));
		write(2, "': ", 3);
	}
	if (msg3)
		write(2, msg3, ft_strlen(msg3));
}

void	lex_error_function(char *word, int syntax_erorr)
{
	if (syntax_erorr == 1)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, word, ft_strlen(word));
		write(2, "'\n", 2);
	}
	else
	{
		write(2, "minishell: unexpected newline while" \
				" looking for matching `", 58);
		write(2, word, 1);
		write(2, "'\n", 2);
	}
}

void	token_order_error(t_token *temp, int open_brackets)
{
	if (open_brackets == -1)
		lex_error_function(temp->word, 1);
	else if (temp->type == NEW_LINE || temp->next->type == NEW_LINE)
		lex_error_function("newline", 1);
	else
		lex_error_function(temp->next->word, 1);
}
