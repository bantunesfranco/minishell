/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bruno <bruno@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:27:34 by bruno         #+#    #+#                 */
/*   Updated: 2023/05/03 15:20:21 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include <fcntl.h>

int	main(int argc, char **argv, char **envp)
{
	char		**env;
	t_cmd		cmd;
	t_redirect	*out;

	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	env = ft_arrdup(envp);
	out = malloc(sizeof(t_redirect));
	// out->fd = open("res.txt", O_RDWR);
	out->fd = 1;
	if (out->fd == -1)
		exit(1);
	cmd.output = out;
	cd(env, &cmd);
	ft_free_arr(env);
	exit(0);
}