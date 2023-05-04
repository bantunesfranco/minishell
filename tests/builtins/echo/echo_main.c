/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 17:03:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/04 12:34:20 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include <fcntl.h>

int	main(int argc, char **argv, char **envp)
{
	t_cmd		cmd;
	t_gen		gen;

	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	gen.env = ft_arrdup(envp);
	cmd.output = malloc(sizeof(t_redirect));
	if (argv[2])
		cmd.output->fd = open(argv[2], O_RDWR);
	else
		cmd.output->fd = 1;
	echo(&gen, &cmd);
	ft_free_arr(gen.env);
	exit(0);
}
