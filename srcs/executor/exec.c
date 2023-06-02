/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 12:59:41 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/02 10:52:26 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	handle_dups(t_cmd *cmd, int *p, int pipe_rd)
{
	if (p[0] != -1)
	{
		if (cmd->prev && cmd->input->fd == STDIN_FILENO)
			if (dup2(pipe_rd, STDIN_FILENO) == -1)
				child_err_msg(NULL, "executor in");
		if (cmd->next && cmd->output->fd == STDOUT_FILENO)
			if (dup2(p[1], STDOUT_FILENO) == -1)
				child_err_msg(NULL, "executor");
	}
	if (cmd->input->fd != STDIN_FILENO)
	{
		// close(pipe_rd);
		if (dup2(cmd->input->fd, STDIN_FILENO) == -1)
			child_err_msg(NULL, "executor");
	}
	if (cmd->output->fd != STDOUT_FILENO)
	{
		if (dup2(cmd->output->fd, STDOUT_FILENO) == -1)
			child_err_msg(NULL, "executor");
	}
}

int	pipe_and_fork(t_cmd *cmd, int *p)
{
	int	id;

	if (cmd->next || cmd->prev)
	{
		if (pipe(p) == -1)
		{
			err_msg(NULL, "executor");
			return (-1);
		}
		// printf("p[0] = %d\tp[1] = %d\n", p[0], p[1]);
	}
	else
	{
		p[0] = -1;
		p[1] = -1;
	}
	id = fork();
	if (id == -1)
	{
		err_msg(NULL, "executor");
		return (-1);
	}
	return (id);
}

void	close_pipes(t_cmd *cmd, int *p, int pipe_rd)
{
	(void)pipe_rd;
	// if (p[0] != -1 && cmd->prev = NULL && pipe_rd != STDIN_FILENO)
		// close(pipe_rd);
	if (p[1] != -1 && !cmd->next)
		close(p[1]);
	// if (p[0] != -1 && cmd->prev && cmd->input->fd != STDIN_FILENO)
		// close(pipe_rd);
	if (p[1] != -1 && cmd->next && cmd->output->fd != STDOUT_FILENO)
		close(p[1]);
	// printf("close ----> p[0] = %d\tp[1] = %d\n", p[0], p[1]);
}

// void	executor(t_gen *gen, t_pipeline *pipeline)
// {
// 	t_cmd	*cmd;
// 	t_cmd	*cmd2;
// 	int		p[2];
// 	int		id;
// 	int		status;

// 	cmd = pipeline->first_cmd;
// 	id = pipe_and_fork(cmd, p);
// 	// if (cmd->builtin != NULL)
// 	// {
// 	// 	cmd->builtin(gen, cmd);
// 	// 	return ;
// 	// }
// 	if (id == 0)
// 	{
// 		// close(p[0]);
// 		cmd->input->fd = handle_input_redirection(cmd->input);
// 		cmd->output->fd = handle_output_redirection(cmd->output);
// 		find_path(cmd->cmd, gen);
// 		check_access(gen, cmd);
// 		handle_dups(cmd, p);
// 		close_pipes(cmd, p);

// 		execve(cmd->path, cmd->cmd, gen->env);
// 		err_msg(NULL, cmd->cmd[0]);
// 		_exit(errno);
// 	}
// 	else
// 	{
// 		cmd2 = cmd->next;
// 		cmd2->input->fd = handle_input_redirection(cmd2->input);
// 		cmd2->output->fd = handle_output_redirection(cmd2->output);
// 		int id2 = fork();
// 		if (id2 == 0)
// 		{
// 			find_path(cmd2->cmd, gen);
// 			check_access(gen, cmd2);
// 			handle_dups(cmd2, p);
// 			close_pipes(cmd2, p);
// 			execve(cmd2->path, cmd2->cmd, gen->env);
// 			err_msg(NULL, cmd2->cmd[0]);
// 			_exit(errno);
// 		}
// 		else
// 		{
// 			// close(p[0]);
// 			// close(p[1]);
// 			waitpid(id, &status, 0);
// 			waitpid(id2, &status, 0);
// 		}
// 	}
// 	// if (WIFEXITED(status))
// 	// 	exit(WEXITSTATUS(status));
// 	// exit(1);
// }
