/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_here_doc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:58:04 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/28 13:31:38 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "libft.h"
#include "parsing_structs.h"
#include "parsing.h"
#include "minishell.h"
#include <readline/readline.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
// #include "readline.h"

char	*read_loop(char *del, int p)
{
	char	*line;
	char	*str;
	// char	*tmp;

	errno = 0;
	str = ft_strdup("");
	if (!str)
		err_msg(NULL, "here_doc");
	while (1)
	{
		write(0, "> ", 2);
		// system("leaks -q minishell");
		line = get_next_line(0);
		if (line == NULL && errno != 0)
		{
			err_msg(NULL, "here_doc");
			exit(errno);
		}
		else if (g_kill_switch == 1)
			return (free(line), free(str), NULL);
		else if (line == NULL && errno == 0)
		{
			// printf("hi\n");
			// system("leaks -q minishell");
			return (str);
		}
		// *(line + ft_strlen(line) - 1) = '\0';
		if (!ft_strncmp(line, del, ft_strlen(del) + 1))
			break ;
		// *(line + ft_strlen(line)) = '\n';
		// tmp = line;
		// line = ft_strjoin(tmp, "\n");
		// free(tmp);
		// if (line == NULL)
		// 	err_msg(NULL, "here_doc");
		str = ft_strjoin_free(str, line);
		if (!str)
			err_msg(NULL, "here_doc");
	}
	free(line);
	return (str);
}

// char	*read_loop(char *del)
// {
// 	char	*line;
// 	char	*str;
// 	char	*tmp;

// 	errno = 0;
// 	str = ft_strdup("");
// 	if (!str)
// 		err_msg(NULL, "here_doc");
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (line == NULL && errno == ENOMEM)
// 			err_msg(NULL, "here_doc");
// 		else if (g_kill_switch == 1)
// 			return (free(line), free(str), NULL);
// 		else if (line == NULL && errno == 0)
// 			return (str);
// 		if (!ft_strncmp(line, del, ft_strlen(del) + 1))
// 			break ;
// 		tmp = line;
// 		line = ft_strjoin(tmp, "\n");
// 		free(tmp);
// 		if (line == NULL)
// 			err_msg(NULL, "here_doc");
// 		str = ft_strjoin_free(str, line);
// 		if (!str)
// 			err_msg(NULL, "here_doc");
// 	}
// 	return (str);
// }

bool	remove_quotes(char *new_del)
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
			{
				return (false);
			}
			ft_memmove(new_del + i, new_del + i + 1, ft_strlen(new_del + i));
			ft_memmove(new_del + j - 1, new_del + j, ft_strlen(new_del + j - 1));
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

	close(p[0]);
	new_delimiter = ft_strjoin(delimiter, "\n");
	if (new_delimiter == NULL)
		err_msg(NULL, "here_doc");
	if (!remove_quotes(new_delimiter))
	{
		free(new_delimiter);
		return ;
	}
	read_loop(new_delimiter, p[1]);
	free(new_delimiter);
	_exit(0);
}

int	parent_heredoc(t_token *current_node)
{

}

int	read_heredoc(t_token *current_node, char *delimiter)
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
	return (parent_heredoc(current_node));
	// current_node->str = read_loop(new_delimiter);
}

void	count_heredocs(t_token *first_token, t_token *error_token)
{
	int	i;

	i = 0;
	while (first_token != error_token)
	{
		if (first_token->type == LESS_LESS)
			i++;
		if (i > 16)
		{
			write(2, "minishell: maximum here-document count exceeded\n", 48);
			exit (2);
		}
		first_token = first_token->next;
	}
}

void	read_heredocs(t_token *first_token, t_token *error_token)
{
	t_token	*temp;

	g_kill_switch = 0;
	count_heredocs(first_token, error_token);
	// setup_signal_handlers_and_terminal_interactive();
	signal(SIGINT, heredoc_handler);
	temp = first_token;
	while (temp != error_token)
	{
		if (temp->type == LESS_LESS)
			read_heredoc(temp, temp->next->word);
		if (g_kill_switch == 1)
			return ;
		temp = temp->next;
	}
	// system("leaks -q minishell");
}

// int	main(void)
// {
// 	char	*str;

// 	str = read_here_doc("\"EOF\"");
// 	// printf("%zd\n", write(1, "jtydjtyjty", 0));
// 	printf("str: %s", str);
// 	free(str);
// 	return (0);
// }
