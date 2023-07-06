/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_child.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 10:32:07 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:45:10 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include <signal.h>

static void	read_loop(char *del, int p)
{
	char	*line;

	errno = 0;
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(0);
		if (line == NULL && errno != 0)
		{
			close(p);
			child_err_msg(NULL, "here_doc");
		}
		else if (line == NULL)
			break ;
		if (!ft_strncmp(line, del, ft_strlen(del) + 1))
			break ;
		write(p, line, ft_strlen(line));
		free(line);
	}
	close(p);
	free(line);
}

static bool	remove_quotes(char *new_del)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (new_del[i])
	{
		if (new_del[i] == '\'' || new_del[i] == '"')
		{
			j = skip_quotes(new_del, i);
			if (new_del[j] == '\0')
				return (false);
			ft_memmove(new_del + i, new_del + i + 1, ft_strlen(new_del + i));
			ft_memmove(new_del + j - 1, new_del + j, \
						ft_strlen(new_del + j - 1));
			i = j - 1;
		}
		else
			i++;
	}
	return (true);
}

void	child_heredoc(char *delimiter, int p[2])
{
	char	*new_delimiter;

	signal(SIGINT, SIG_DFL);
	close(p[0]);
	new_delimiter = ft_strjoin(delimiter, "\n");
	if (new_delimiter == NULL)
		child_err_msg(NULL, "here_doc");
	if (!remove_quotes(new_delimiter))
	{
		free(new_delimiter);
		_exit(1);
	}
	read_loop(new_delimiter, p[1]);
	free(new_delimiter);
	_exit(0);
}
