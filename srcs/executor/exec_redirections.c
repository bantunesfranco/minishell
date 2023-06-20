/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_redirections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 09:35:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/19 15:28:47 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <fcntl.h>

int	handle_input_redirection(t_redirect *input)
{
	t_redirect	*head;

	if (!input || !input->name)
		return (STDIN_FILENO);
	head = input;
	while (head)
	{
		if (head->type == INPUT)
		{
			head->fd = open(head->name, O_RDONLY);
			if (head->fd == -1)
				return (err_msg(NULL, head->name), -1);
		}
		// if (head->type == HEREDOC)
		// 	head->fd = open_here_doc(head);
		if (!head->next)
			break ;
		close(head->fd);
		head = head->next;
	}
	return (head->fd);
}

int	handle_output_redirection(t_redirect *output)
{
	t_redirect	*head;

	if (!output || !output->name)
		return (STDOUT_FILENO);
	head = output;
	while (head)
	{
		if (head->type == OUTPUT)
		{
			head->fd = open(head->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			if (head->fd == -1)
				return (err_msg(NULL, head->name), -1);
		}
		else if (head->type == APPEND)
		{
			head->fd = open(head->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
			if (head->fd == -1)
				return (err_msg(NULL, head->name), -1);
		}
		if (!head->next)
			break ;
		close(head->fd);
		head = head->next;
	}
	return (head->fd);
}
