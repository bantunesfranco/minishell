/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:53:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/26 16:20:14 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target(char *target, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_envcmp(env[i], target))
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	if (!ft_strncmp(target, "OLDPWD=", 8))
		return (built_err_msg("cd", NULL, "OLDPWD not set\n"), NULL);
	else if (!ft_strncmp(target, "HOME=", 6))
		return (built_err_msg("cd", NULL, "HOME not set\n"), NULL);
	else
		return (target);
}

char	**if_unset(char *target, char *cwd, char **env)
{
	char	*var;
	char	**new_env;

	var = ft_strjoin(target, cwd);
	free(cwd);
	if (!var)
		return (err_msg(NULL, "cd"), -1);
	new_env = copy_env(env, var, ft_arrlen(env) + 1);
	free(var);
	if (!new_env)
		return (err_msg(NULL, "cd"), NULL);
}

static int	set_env_vars(char *target, char **env)
{
	int		i;
	char	*cwd;
	char	*tmp;

	i = 0;
	temp = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (err_msg(NULL, "cd"), -1);
	while (env[i] && ft_envcmp(env[i], target))
		i++;
	if (!env[i])
	{
		env = if_unset(target, cwd, env);
		return (0);
	}
	temp = env[i];
	env[i] = ft_strjoin(target, cwd);
	if (!env[i])
		return (free(cwd), err_msg(NULL, "cd"), -1);
	free(tmp);
	free(cwd);
	return (0);
}

static int	go_to(char *target, t_gen *gen)
{
	char	*path;

	path = get_target(target, gen->env);
	if (!path)
		return (-1);
	if (set_env_vars("OLDPWD=", gen->env) == -1)
		return (-1);
	if (chdir(path) == -1)
		return (err_msg("cd", path), -1);
	if (set_env_vars("PWD=", gen->env) == -1)
		return (-1);
	return (0);
}

int	cd(t_gen *gen, t_cmd *cmd)
{
	char	*old;

	old = NULL;
	if (ft_arrlen(cmd->cmd) > 2)
		return (built_err_msg(cmd->cmd[0], NULL, "too many arguments\n"), -1);
	if (!cmd->cmd[1] || !ft_strncmp(cmd->cmd[1], "--", 3))
		if (go_to("HOME=", gen) == -1)
			return (-1);
	else if (!ft_strncmp(cmd->cmd[1], "-", 2))
	{
		if (go_to("OLDPWD=", gen) == -1)
			return (-1);
		old = getcwd(NULL, 0);
		if (write(cmd->output->fd, old, ft_strlen(old)) == -1)
			return (free(old), err_msg(NULL, cmd->cmd[0]), -1);
		free(old);
		if (write(cmd->output->fd, "\n", 1) == -1)
			return (err_msg(NULL, cmd->cmd[0]), -1);
	}
	else
		if (go_to(cmd->cmd[1], gen) == -1)
			return (-1);
	return (0);
}
