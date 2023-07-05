/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_redirections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 09:35:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/05 18:19:13 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"
#include <fcntl.h>

static int	handle_input_redir(t_redirect *node, t_gen *gen)
{
	if (expand_redirect(&(node->name), gen) == false)
	{
		built_err_msg(node->name, NULL, "ambiguous redirect\n");
		return (-1);
	}
	node->fd = open(node->name, O_RDONLY);
	if (node->fd == -1)
	{
		err_msg(NULL, node->name);
		return (-1);
	}
	return (node->fd);
}

static int	handle_output_redir(t_redirect *node, t_gen *gen)
{
	if (expand_redirect(&(node->name), gen) == false)
	{
		built_err_msg(node->name, NULL, "ambiguous redirect\n");
		return (-1);
	}
	node->fd = open(node->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (node->fd == -1)
	{
		err_msg(NULL, node->name);
		return (-1);
	}
	return (node->fd);
}

static int	handle_append_redir(t_redirect *node, t_gen *gen)
{
	if (expand_redirect(&(node->name), gen) == false)
	{
		built_err_msg(node->name, NULL, "ambiguous redirect\n");
		return (-1);
	}
	node->fd = open(node->name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (node->fd == -1)
	{
		err_msg(NULL, node->name);
		return (-1);
	}
	return (node->fd);
}

int	handle_input_redirection(t_redirect *input, t_gen *gen)
{
	t_redirect	*head;

	if (!input || !input->name)
		return (STDIN_FILENO);
	head = input;
	while (head)
	{
		if (head->type == INPUT)
			head->fd = handle_input_redir(head, gen);
		else if (head->type == HEREDOC && !head->next)
			head->fd = handle_heredoc_redir(head, gen);
		if (head->fd == -1)
			return (-1);
		if (!head->next)
			break ;
		close(head->fd);
		head = head->next;
	}
	return (head->fd);
}

int	handle_output_redirection(t_redirect *output, t_gen *gen)
{
	t_redirect	*head;

	if (!output || !output->name)
		return (STDOUT_FILENO);
	head = output;
	while (head)
	{
		if (head->type == OUTPUT)
			head->fd = handle_output_redir(head, gen);
		else if (head->type == APPEND)
			head->fd = handle_append_redir(head, gen);
		if (head->fd == -1)
			return (-1);
		if (!head->next)
			break ;
		close(head->fd);
		head = head->next;
	}
	return (head->fd);
}
