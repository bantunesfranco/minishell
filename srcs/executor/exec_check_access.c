/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_check_access.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:04:23 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/24 12:53:00 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <sys/wait.h>

static int	check_rel_path(t_cmd *cmd, int p)
{
	char	*tmp;

	if ((!ft_strchr(cmd->cmd[0], '/') || cmd->cmd[0][0] == '/') && p == 1)
		return (1);
	cmd->path = getcwd(NULL, 1);
	if (!cmd->path && errno == ENOMEM)
		return (err_msg(NULL, "check path"), 1);
	else if (!cmd->path)
		return (1);
	tmp = ft_strjoin(cmd->path, "/");
	free(cmd->path);
	if (!tmp)
		return (err_msg(NULL, "check path"), 1);
	cmd->path = ft_strjoin(tmp, cmd->cmd[0]);
	free(tmp);
	if (!cmd->path)
		return (err_msg(NULL, "check path"), 1);
	if (access(cmd->path, F_OK) || access(cmd->path, X_OK))
	{
		err_msg(NULL, cmd->cmd[0]);
		if (errno == 13)
			_exit(126);
		_exit(errno);
	}
	return (0);
}

static int	check_abs_path(t_cmd *cmd)
{
	if (cmd->cmd[0][0] != '/')
		return (1);
	if (access(cmd->cmd[0], F_OK) || access(cmd->cmd[0], X_OK))
	{
		err_msg(NULL, cmd->cmd[0]);
		if (errno == 13)
			_exit(126);
		_exit(errno);
	}
	cmd->path = ft_strdup(cmd->cmd[0]);
	if (!cmd->path)
		return (err_msg(NULL, "check path"), 1);
	return (0);
}

static int	can_access(char *path, t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (err_msg(NULL, "check path"), 0);
	cmd->path = ft_strjoin(tmp, cmd->cmd[0]);
	free(tmp);
	if (!cmd->path)
		return (err_msg(NULL, "check path"), 0);
	if (!access(cmd->path, F_OK) && !access(cmd->path, X_OK))
		return (1);
	else if (errno != ENOENT && errno != ENOTDIR)
	{
		free(cmd->path);
		err_msg(NULL, cmd->cmd[0]);
		_exit(errno);
	}
	free(cmd->path);
	return (0);
}

void	check_access(t_gen *gen, t_cmd *cmd)
{
	int		i;
	// char	*tmp;
	// char	*tmp2
	
	i = 0;
	if (!check_abs_path(cmd))
		return ;
	if (!check_rel_path(cmd, 1))
		return ;
	while (gen->path && gen->path[i])
	{
		if (can_access(gen->path[i], cmd) == 1)
			return ;
		i++;
	}
	if (!gen->path && !check_rel_path(cmd, 0))
		return ;
	errno = 127;
	err_msg(NULL, cmd->cmd[0]);
	_exit(127);
}

// void lks(void)
// {
// 	printf("\n");
// 	system("leaks -q a.out");
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_cmd	cmd;
// 	t_gen	gen;
// 	pid_t	id;
// 	int		status;

// 	(void)argc;
// 	// atexit(lks);
// 	cmd.cmd = ft_split(argv[1], ' ');
// 	gen.env = ft_arrdup(envp);
// 	gen.path = NULL;
// 	find_path(cmd.cmd, &gen);
// 	check_access(&gen, &cmd);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		execve(cmd.path, cmd.cmd, gen.env);
// 		err_msg(NULL, cmd.cmd[0]);
// 		exit(errno);
// 	}
// 	else
// 		waitpid(id, &status, 0);
// 	if (WIFEXITED(status))
// 		exit(WEXITSTATUS(status));
// 	exit(1);
// }
