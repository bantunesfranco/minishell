/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_check_access.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:04:23 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/04 18:51:43 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <dirent.h>
#include <sys/wait.h>

void	is_dir(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir == NULL)
		return ;
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": is a directory\n", 18);
	closedir(dir);
	_exit(126);
}

static int	check_rel_path(t_cmd *cmd, int p)
{
	char	*tmp;

	if ((!ft_strchr(cmd->cmd[0], '/') || cmd->cmd[0][0] == '/') && p == 1)
		return (1);
	is_dir(cmd->cmd[0]);
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
		_exit(127);
	}
	return (0);
}

static int	check_abs_path(t_cmd *cmd)
{
	if (cmd->cmd[0][0] != '/')
		return (1);
	is_dir(cmd->cmd[0]);
	if (access(cmd->cmd[0], F_OK) || access(cmd->cmd[0], X_OK))
	{
		err_msg(NULL, cmd->cmd[0]);
		if (errno == 13)
			_exit(126);
		_exit(127);
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
		_exit(127);
	}
	free(cmd->path);
	return (0);
}

void	check_access(t_gen *gen, t_cmd *cmd)
{
	int		i;

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
