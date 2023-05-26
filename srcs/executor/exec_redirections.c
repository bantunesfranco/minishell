/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_redirections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 09:35:10 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/26 13:59:03 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <fcntl.h>

int	handle_input_redirection(t_redirection *input)
{
	t_redirection	*head;
	int				fd;

	if (!input)
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
		if (head->next)
			close(head->fd);
		head->next;
	}
	return (head->fd);
}

int	handle_output_redirection(t_redirection *output)
{
	t_redirection	*head;
	int				fd;

	if (!output)
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
			head->fd = open(head->name, O_APPEND | O_CREAT | O_RDONLY, 0644);
			if (head->fd == -1)
				return (err_msg(NULL, head->name), -1);
		}
		if (head->next)
			close(head->fd);
		head->next;
	}
	return (head->fd);
}


// int	main(void)
// {
// 	int fd = open("ho.txt", O_RDONLY);
// 	int fd2 = open("ho.txt", O_WRONLY);

// 	printf("fd = %d, fd2 = %d\n" , fd, fd2);
// }
