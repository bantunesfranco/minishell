/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 17:03:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/04 16:23:35 by bfranco       ########   odam.nl         */
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
		cmd.output->fd = 1;
	env(&gen, &cmd);
	export(&gen, &cmd2);
	printf("\n\n\n");
	env(&gen, &cmd);
	ft_free_arr(gen.env);
	exit(0);
}
