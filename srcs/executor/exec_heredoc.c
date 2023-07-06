/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_heredoc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 18:04:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/06 15:18:19 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include <fcntl.h>

void	expand_and_write(t_redirect *heredoc_node, int *p, t_gen *gen)
{
	t_quote_mark	*head;

	close(p[0]);
	head = NULL;
	if (ft_strchr(heredoc_node->name, '\'') == NULL \
		&& ft_strchr(heredoc_node->name, '"') == NULL)
		heredoc_node->str = expand_env(heredoc_node->str, gen, 1, &head);
	free_quote_list(head);
	write(p[1], heredoc_node->str, ft_strlen(heredoc_node->str));
	close(p[1]);
	_exit(0);
}

int	handle_heredoc_redir(t_redirect *heredoc_node, t_gen *gen)
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
		close(p[0]);
		close(p[1]);
		err_msg(NULL, "heredoc");
		return (-1);
	}
	if (id == 0)
		expand_and_write(heredoc_node, p, gen);
	close(p[1]);
	return (p[0]);
}
