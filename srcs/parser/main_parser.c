/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/08 12:29:02 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"
#include <fcntl.h>
#include <sys/wait.h>


// int	main(int argc, char *argv[], char **env)
// {
// 	char	*line;
// 	// char	**input_arr;
// 	int		i;
// 	t_cmd	*lol;
// 	(void)argc;
// 	(void)argv;
// 	(void)env;

// 	while (1)
// 	{
// 		i = 0;
// 		line = readline("minishell$ ");
// 		if (line == NULL)
// 			break ;
// 		lol = parse_line(line);
// 		// printf("%s\n", line);
// 		// input_arr = ft_split_args(line, '|');
// 		// if (!input_arr)
// 		// 	ft_error("minishell: ", ENOMEM);
// 		// print_array(input_arr);
// 		// printf("\n");
// 		// ft_free_arr(input_arr);
// 		// input_arr = NULL;
// 	}
// 	exit(0);
// }

void	leaks(void)
{
	system("leaks parse_test");
}

int	main(int argc, char *argv[], char **env)
{
	// char	*path = "/bin/cat";
	// atexit(leaks);
	// char *cmd[] = {"cat", NULL};	
	(void)argc;
	(void)argv;
	(void)env;
	// 2147483648
	// int pid;
	int	pipe2[2];
	int fd;
	pipe(pipe2);
	fd = open("hi", O_RDWR | O_TRUNC);
	write(fd, "asd\n", 4);
	write(fd, "asa\n", 4);
	// for(int i = 0; 1; i++)
	// char line[10];
	// {
	// write(pipe2[1], "hello\n", 7);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	// dup2(fd, STDIN_FILENO);
	// 	// close(fd);
	// 	close(pipe2[1]);
	// 	dup2(pipe2[0], STDIN_FILENO);
	// 	close(pipe2[0]);
	// 	execve(path, cmd, env);
	// 	printf("error\n");
	// 	exit(1);
	// }

	// sleep(2);
	// write(pipe2[1], "world\n", 7);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	// dup2(fd, STDIN_FILENO);
	// 	// close(fd);
	// 	close(pipe2[1]);
	// 	dup2(pipe2[0], STDIN_FILENO);
	// 	close(pipe2[0]);
	// 	execve(path, cmd, env);
	// 	printf("error\n");
	// 	exit(1);
	// }
	// close(pipe2[1]);
	// waitpid(pid, NULL, 0);
	// printf("parent: %s", line);
	// line[9] = '\0';
	// printf("parent: %s", line);

	// }
	// char *temp = *cmd;
	// cmd++;
	// free(temp);
	// print_array(cmd);

	// printf("%d\n", execve(path, argv, env));
	// chdir("/Users/jmolenaa/Codam/Codam_unfinished/minihell/minishell/incs");
	// execve(path, cmd, env);
	// printf("%d\n", errno);
	// perror("hi");
}
