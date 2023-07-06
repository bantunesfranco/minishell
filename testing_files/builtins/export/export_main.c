/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 17:03:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/09 15:07:31 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include <fcntl.h>

int	main(int argc, char **argv, char **envp)
{
	t_cmd		cmd;
	t_cmd		cmd2;
	t_gen		gen;

	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	cmd2.cmd = ft_split(argv[2], ' ');
	gen.env = ft_arrdup(envp);
	cmd.output = malloc(sizeof(t_redirect));
	cmd2.output = malloc(sizeof(t_redirect));
	if (argv[3])
	{
		cmd.output->fd = open(argv[3], O_RDWR);
		cmd2.output->fd = open(argv[3], O_RDWR);
	}
	else
	{
		cmd.output->fd = 1;
		cmd2.output->fd = 1;
	}
	export(&gen, &cmd2);
	if (cmd2.cmd[1])
		env(&gen, &cmd);
	ft_free_arr(gen.env);
	exit(0);
}
