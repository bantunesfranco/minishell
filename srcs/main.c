/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/04/19 15:37:09 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static void	init_general(t_gen *general, char **envp)
{
	general->env = ft_arrdup(envp);
	if (!general->env)
		exit(1);
	general->pwd = ft_strdup(getenv("PWD") + 4);
	if (!general->pwd)
		exit(1);
	general->oldpwd = ft_strdup(getenv("OLDPWD") + 8);
	if (!general->oldpwd)
		exit(1);
	general->path = ft_split(getenv("PATH"), ':');
	if (!general->path)
		exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_gen general;
	int	i = 0;
	(void)argv;
	if (argc != 1)
		exit(1);
	init_general(&general, envp);
	while (general.path[i])
	{
		printf("%s\n", general.path[i]);
		i++;
	}
	exit(0);
}
