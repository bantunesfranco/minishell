/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_redirections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 09:35:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/27 10:24:38 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"
#include <fcntl.h>

void	expand_and_write(t_redirect *heredoc_node, int *p, t_gen *gen)
{
	t_quote_mark	*head;

	close(p[0]);
	head = NULL;
	if (ft_strchr(heredoc_node->name, '\'') == NULL && ft_strchr(heredoc_node->name, '"') == NULL)
		heredoc_node->str = expand_environment_vars(heredoc_node->str, gen, 1, &head);
	free_quote_list(head);
	write(p[1], heredoc_node->str, ft_strlen(heredoc_node->str));
	close(p[1]);
	_exit(0);
}

int	write_heredoc(t_redirect *heredoc_node, t_gen *gen)
{
	int	id;
	int	p[2];

	if (pipe(p) == -1)
	{
		err_msg(NULL, "heredoc");
		return (-1);
	}
	id = fork();
	if (id == -1)
	{
		err_msg(NULL, "heredoc");
		return (-1);
	}
	if (id == 0)
	{
		expand_and_write(heredoc_node, p, gen);
	}
	close(p[1]);
	return (p[0]);
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
		{
			if (expand_redirect(&(head->name), gen) == false)
				return (built_err_msg(head->name, NULL, "ambiguous redirect\n"), -1);
			head->fd = open(head->name, O_RDONLY);
			if (head->fd == -1)
				return (err_msg(NULL, head->name), -1);
		}
		if (head->type == HEREDOC && !head->next)
			head->fd = write_heredoc(head, gen);
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
		{
			if (expand_redirect(&(head->name), gen) == false)
				return (built_err_msg(head->name, NULL, "ambiguous redirect\n"), -1);
			head->fd = open(head->name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
			if (head->fd == -1)
				return (err_msg(NULL, head->name), -1);
		}
		else if (head->type == APPEND)
		{
			if (expand_redirect(&(head->name), gen) == false)
				return (built_err_msg(head->name, NULL, "ambiguous redirect\n"), -1);
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
