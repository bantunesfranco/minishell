/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/19 16:53:33 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/20 12:22:17 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arrdup(char **arr);

void	cd_to_path(char *str, char **envp)
{
	char	*pwd;
	char	*old_pwd;
	char	*path;
	int		i;

	i = 0;
	path = getcwd(NULL, 0);
	old_pwd = ("OLD_PWD=", path);
	chdir(getenv(str));
	pwd = getcwd(NULL, 0);
	while (envp[i])
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
		i++;
	}
	// exit(0);
}

void	cd(char *str, char **envp)
{
	if (!str ||)
		cd_to_path("HOME=", envp);
	else
		cd_to_path(str, envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	int		i;

	i = 0;
	(void)argc;
	env = ft_arrdup(envp);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	cd_to_path(argv[1], env);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	ft_free_arr(env);
	exit(0);
}