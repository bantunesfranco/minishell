/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bruno <bruno@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:27:34 by bruno         #+#    #+#                 */
/*   Updated: 2023/05/10 13:36:29 by bfranco       ########   odam.nl         */
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
	char	*old;

	// atexit(lks);
	(void)argc;
	cmd.cmd = ft_split(argv[1], ' ');
	cmd2.cmd = ft_split(argv[2], ' ');
	gen.env = ft_arrdup(envp);
	cmd.output = malloc(sizeof(t_redirect));
	cmd2.output = malloc(sizeof(t_redirect));
	cmd.output->fd = 1;
	cmd2.output->fd = 1;
	pwd(&gen, &cmd);
	old = getenv("OLDPWD");
	if (old)
		gen.oldpwd = ft_strdup(old);
	else
		gen.oldpwd = NULL;
	gen.pwd = getcwd(NULL, 1);
	if (cd(&gen, &cmd2) == -1)
		exit(1);
	write(cmd.output->fd, "                 ", 17);
	pwd(&gen, &cmd);
	ft_free_arr(gen.env);
	exit(0);
}
