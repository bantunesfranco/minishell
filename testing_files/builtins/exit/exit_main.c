/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 17:03:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/07 10:01:27 by codespace     ########   odam.nl         */
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
	gen.status = 0;
	mini_exit(&gen, &cmd);
}
