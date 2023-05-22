/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_find_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 12:30:34 by codespace     #+#    #+#                 */
/*   Updated: 2023/05/22 16:57:25 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <sys/wait.h>

char	**find_path(char **cmd, char **env)
{
	int		i;
	char	**path_arr;

	i = 0;
	path_arr = NULL;
	while (env[i])
	{
		if (!ft_envcmp(env[i], "PATH="))
		{
			path_arr = ft_split(env[i] + 5, ':');
			if (!path_arr)
				return (err_msg(NULL, cmd[0]), NULL);
		}
		i++;
	}
	if (!path_arr)
	{
		errno = 127;
		err_msg(NULL, cmd[0]);
		exit (127);
	}
	else
		return (path_arr);
}


int	check_abs_path(char *cmd)
{
	if (cmd[0] != '/')
		return (1);
	if (access(cmd, F_OK))
	{
		err_msg(NULL, cmd);
		exit(errno);
	}
	// if (access(cmd, X_OK))
	// {
	// 	err_msg(NULL, cmd);
	// 	exit(errno);
	// }
	return (0);
}

int	can_access(t_cmd *cmd, int i)
{
	char	*tmp;
	char	*fpath;

	tmp = ft_strjoin(cmd->path[i], "/");
	if (!tmp)
		return (err_msg(NULL, cmd->cmd[0]), 0);
	fpath = ft_strjoin(tmp, cmd->cmd[0]);
	if (!fpath)
		return (free(tmp), err_msg(NULL, cmd->cmd[0]), 0);
	free(tmp);
	if (!access(fpath, F_OK)) //&& !access(fpath, X_OK))
	{
		free(cmd->cmd[0]);
		cmd->cmd[0] = fpath;
		return (1);
	}
	else if (errno != ENOENT)
	{
		free(fpath);
		err_msg(NULL, cmd->cmd[0]);
		exit(errno);
	}
	free(fpath);
	return (0);
}

int	check_access(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!check_abs_path(cmd->cmd[0]))
		return (0);
	while (cmd->path[i])
	{
		if (can_access(cmd, i) == 1)
			return (0);
		i++;
	}
	errno = 127;
	err_msg(NULL, cmd->cmd[0]);
	exit(127);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	t_gen	gen;
	pid_t	id;
	int		status;

	// atexit(lks);
	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	gen.env = ft_arrdup(envp);
	cmd.path = find_path(cmd.cmd, gen.env);
	int i = check_access(&cmd);
	printf("Can acces?\t%s\n", i ? "False":"True");
	id = fork();
	if (id == 0)
	{
		execve(cmd.cmd[0], cmd.cmd, gen.env);
		err_msg(NULL, cmd.cmd[0]);
		exit(errno);
	}
	else
		waitpid(id, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(1);
}
