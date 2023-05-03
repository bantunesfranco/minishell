/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_main2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bruno <bruno@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 10:00:21 by bruno         #+#    #+#                 */
/*   Updated: 2023/05/03 10:00:24 by bruno         ########   odam.nl         */
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
	pwd(env, &cmd);
    chdir("..");
    write(out->fd, "                 ", 17);
    pwd(env, &cmd);
	ft_free_arr(env);
	exit(0);
}