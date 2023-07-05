/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bruno <bruno@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:27:34 by bruno         #+#    #+#                 */
/*   Updated: 2023/07/05 13:31:32 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include <fcntl.h>

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	t_cmd	cmd2;
	t_gen	gen;

	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	cmd2.cmd = ft_split(argv[2], ' ');
	gen.env = ft_arrdup(envp);
	cmd.output = malloc(sizeof(t_redirect));
	cmd.output->fd = 1;
	unset(&gen, &cmd2);
	env(&gen, &cmd);
	ft_free_arr(gen.env);
	exit(0);
}
