/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:53:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/21 15:02:47 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

int	change_dir(char *str)
{
	const char	*special[2] = {"HOME=", "-"};
	char		*pwd;
	char		*temp;
	int			i;

	i = 0;
	while (i < 2)
	{
		if (!ft_strncmp(special[i], str, ft_strlen(special[i]) + 1))
		{
			pwd = getenv(str);
			if (!pwd)
				return (perror("minishell:"), -1);
			return (chdir(pwd), 0);
		}
		i++;
	}
	pwd = getenv("PWD=");
	temp = ft_strjoin(pwd, "/");
	if (!temp)
		return (perror("minishell:"), -1);
	pwd = ft_strjoin(temp, str);
	if (!pwd)
		return (perror("minishell:"), -1);
	return (chdir(pwd), 0);
}

void	change_pwd(char **envp, char *pwd, char *old_pwd)
{
	int	i;

	i = -1;
	if (envp)
	{
		while (envp[++i])
		{
			if (!ft_strncmp("OLD_PWD=", envp[i], 8))
			{
				free(envp[i]);
				envp[i] = old_pwd;
			}
			if (!ft_strncmp("PWD=", envp[i], 4))
			{
				free(envp[i]);
				envp[i] = pwd;
			}
		}
	}
}

char	*get_pwd(char *str)
{
	char	*pwd;
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (perror("minishell:"), NULL);
	pwd = ft_strjoin(str, path);
	if (!pwd)
		return (perror("minishell:"), free(path), NULL);
	return (free(path), pwd);
}

int	cd_to_path(char *str, char **envp)
{
	int		i;
	char	*pwd;
	char	*old_pwd;

	i = 0;
	old_pwd = get_pwd("OLD_PWD=");
	if (!old_pwd)
		return (-1);
	if (change_dir(str) == -1)
		return (-1);
	pwd = get_pwd("PWD=");
	if (!pwd)
		return (-1);
	change_pwd(envp, pwd, old_pwd);
	// free(pwd);
	// free(old_pwd);
	// pwd = pwd;
	// old_pwd = old_pwd;
	return (0);
}

void	cd(char **envp, t_cmd *cmd)
{
	if (!cmd->cmd[1] || !ft_strncmp("~", cmd->cmd[1], 2))
		cd_to_path("HOME=", envp);
	else if (!ft_strncmp("-", cmd->cmd[1], 2))
		cd_to_path("OLD_PWD=", envp);
	else
		cd_to_path(cmd->cmd[1], envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	int		i;
	t_cmd	cmd;
	t_cmd	cmd2;

	i = 0;
	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	cmd2.cmd = ft_split(argv[2], ' ');
	env = ft_arrdup(envp);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	cd(env, &cmd);
	i = 0;
	printf("\n\n");
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	cd(env, &cmd2);
	i = 0;
	printf("\n\n");
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	ft_free_arr(env);
	exit(0);
}
