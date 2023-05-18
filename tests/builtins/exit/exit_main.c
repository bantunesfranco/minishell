/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 17:03:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/18 11:55:53 by codespace     ########   odam.nl         */
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
	mini_exit(&gen, &cmd);
	ft_free_arr(gen.env);
	exit(0);
}
