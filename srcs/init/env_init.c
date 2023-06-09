/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 17:35:46 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/04 16:22:15 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static int	get_size(char **env)
{
	int	i;
	int	size;

	size = ft_arrlen(env) + 4;
	i = 0;
	while (env[i])
	{
		if (!ft_envcmp(env[i], "OLDWD="))
			size--;
		if (!ft_envcmp(env[i], "SHLVL="))
			size--;
		if (!ft_envcmp(env[i], "PWD="))
			size--;
		i++;
	}
	return (size);
}

void	add_extra_vars(char **new_env, int *vars, int *j)
{
	char	*cwd;

	cwd = NULL;
	if (vars[0] == 0)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			err_msg(NULL, "env init");
		new_env[*j] = ft_strjoin("PWD=", cwd);
		free(cwd);
		if (!new_env[*j])
			err_msg(NULL, "env init");
		(*j)++;
	}
	if (vars[1] == 0)
	{
		new_env[*j] = ft_strdup("SHLVL=1");
		if (!new_env[*j])
			err_msg(NULL, "env init");
	}
}

void	get_shlvl(char **new_env, char *env, int *j, int *vars)
{
	int		shlvl;
	char	*shlvl_var;

	shlvl = ft_atoi(env + 6);
	if (shlvl >= 999)
		built_err_msg("warning", NULL, \
		"shell level (>999) too high, resetting to 1\n");
	if (shlvl <= 0 || shlvl >= 999)
		shlvl = 1;
	else
		shlvl++;
	shlvl_var = ft_itoa(shlvl);
	if (!shlvl_var)
		err_msg(NULL, "env init");
	new_env[*j] = ft_strjoin("SHLVL=", shlvl_var);
	free(shlvl_var);
	if (!new_env[*j])
		err_msg(NULL, "env init");
	free(env);
	vars[1] = 1;
}

void	copy_var(char **new_env, char **env, int *i, int *j)
{
	static int	vars[2] = {0, 0};

	if (!ft_envcmp(env[*i], "SHELL="))
	{
		free(env[*i]);
		new_env[*j] = ft_strdup("SHELL=minishell");
		if (!new_env[*j])
			err_msg(NULL, "env init");
	}
	else if (!ft_envcmp(env[*i], "SHLVL="))
		get_shlvl(new_env, env[*i], j, vars);
	else
	{
		if (!ft_envcmp(env[*i], "PWD="))
			vars[0] = 1;
		new_env[*j] = env[*i];
	}
	(*i)++;
	(*j)++;
	if (!env[*i])
		add_extra_vars(new_env, vars, j);
}

char	**env_init(char **env)
{
	int		size;
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = get_size(env);
	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (err_msg(NULL, "env init"), NULL);
	while (env[i])
	{
		if (!ft_envcmp(env[i], "OLDWD="))
			free(env[i++]);
		else
			copy_var(new_env, env, &i, &j);
	}
	free(env);
	return (new_env);
}
