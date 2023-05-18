/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bruno <bruno@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:27:34 by bruno         #+#    #+#                 */
/*   Updated: 2023/05/18 19:57:39 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include <fcntl.h>

// void	lks(void)
// {
// 	system("leaks -q a.out");
// }

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	t_cmd	cmd2;
	t_gen	gen;

	// atexit(lks);
	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	cmd2.cmd = ft_split(argv[2], ' ');
	gen.env = ft_arrdup(envp);
	cmd.output = malloc(sizeof(t_redirect));
	cmd2.output = malloc(sizeof(t_redirect));
	cmd.output->fd = 1;
	if (argv[3])
		cmd2.output->fd = open(argv[3], O_RDWR);
	else
		cmd2.output->fd = 1;
	pwd(&gen, &cmd);
	if (cd(&gen, &cmd2) == -1)
		exit(1);
	write(cmd.output->fd, "                 ", 17);
	pwd(&gen, &cmd);
	ft_free_arr(gen.env);
	exit(0);
}
