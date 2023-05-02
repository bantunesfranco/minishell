/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_main2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 17:03:58 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/02 19:04:13 by bruno         ########   odam.nl         */
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
	out->fd = open("res.txt", O_RDWR);
	if (out->fd == -1)
		exit(1);
	cmd.output = out;
	echo(env, &cmd);
	ft_free_arr(env);
	exit(0);
}
