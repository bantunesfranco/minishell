/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/03 13:04:45 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static void	init_general(t_gen *general, char **envp)
{
	general->env = ft_arrdup(envp);
	if (!general->env)
		exit(1);
	general->pwd = getcwd();
	if (!general->pwd)
		exit(1);
	general->oldpwd = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_gen	general;
	int		i;

	i = 0;
	(void)argv;
	if (argc != 1)
		exit(1);
	init_general(&general, envp);
	while (general.env[i])
	{
		printf("%s\n", general.env[i]);
		i++;
	}
	exit(0);
}
