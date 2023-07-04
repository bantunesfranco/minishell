/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parent.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:58:04 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/04 18:32:31 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include <signal.h>

static char	*read_from_pipe(int p)
{
	char	*str;
	char	buf[10];
	char	*temp;
	int		read_bytes;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	while (1)
	{
		read_bytes = read(p, buf, 9);
		if (read_bytes == -1)
			return (free(str), NULL);
		else if (read_bytes == 0)
			break ;
		buf[read_bytes] = '\0';
		temp = str;
		str = ft_strjoin(str, buf);
		free(temp);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

static int	parent_heredoc(t_token *current_node, int p[2], int child_id)
{
	int	status;

	close(p[1]);
	current_node->str = read_from_pipe(p[0]);
	close(p[0]);
	if (current_node->str == NULL)
	{
		kill(child_id, SIGINT);
		err_msg(NULL, "here_doc");
		return (-1);
	}
	waitpid(child_id, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}

static int	read_single_heredoc(t_token *current_node, char *delimiter)
{
	int		id;
	int		p[2];

	if (pipe(p) == -1)
	{
		err_msg(NULL, "here_doc");
		return (-1);
	}
	id = fork();
	if (id == -1)
	{
		err_msg(NULL, "here_doc");
		return (-1);
	}
	if (id == 0)
		child_heredoc(delimiter, p);
	return (parent_heredoc(current_node, p, id));
}

static void	count_heredocs(t_token *head, t_token *error_token)
{
	int	i;

	i = 0;
	while (head != error_token)
	{
		if (head->type == LESS_LESS)
			i++;
		if (i > 16)
		{
			write(2, "minishell: maximum here-document count exceeded\n", 48);
			exit(2);
		}
		head = head->next;
	}
}

int	read_all_heredocs(t_token *head, t_token *error_token)
{
	t_token	*temp;
	int		error;

	count_heredocs(head, error_token);
	signal(SIGQUIT, SIG_IGN);
	unset_echoctl();
	temp = head;
	while (temp != error_token)
	{
		if (temp->type == LESS_LESS)
		{
			error = read_single_heredoc(temp, temp->next->word);
			if (error != 0)
				return (error);
		}
		temp = temp->next;
	}
	return (0);
}
