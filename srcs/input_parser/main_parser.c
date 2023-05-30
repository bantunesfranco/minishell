/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/30 16:58:11 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// void	malloc_failure()
// {
// 	perror("minishell ");
// 	exit(errno);
// }

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

// int	main(int argc, char *argv[], char **env)
// {
// 	char	*line;
// 	char 	*line2;
// 	// char	**input_arr;
// 	t_pipeline	*lol;
// 	(void)argc;
// 	(void)argv;
// 	(void)env;

// 	atexit(leaks);
// 	while (1)
// 	{
// 		if (isatty(STDIN_FILENO))
// 			line = readline("minishell$ ");
// 		else
// 		{
// 			line2 = get_next_line(STDIN_FILENO);
// 			if (line2 == NULL)
// 				break ;
// 			line = ft_strtrim(line2, "\n");
// 			free(line2);
// 		}
// 		if (line == NULL)
// 			break ;
// 		lol = parse_line(line);
// 		if (lol == NULL)
// 			printf("Syntax error\n");
// 		free(line);
// 		lol++;
// 		// printf("%s\n", line);
// 		// input_arr = ft_split_args(line, '|');
// 		// if (!input_arr)
// 		// 	ft_error("minishell: ", ENOMEM);
// 		// print_array(input_arr);
// 		// printf("\n");
// 		// ft_free_arr(input_arr);
// 		// input_arr = NULL;
// 	}
// 	// printf("\ndone\n\n");
// 	return (0);
// }

// int	main(int argc, char *argv[], char **env)
// {
// 	char	*path = "/Users/jmolenaa/Codam/Codam_unfinished/minihell/minishell/script.sh";
// 	// atexit(leaks);
// 	char *cmd[] = {"script.sh", NULL};	
// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// 	// 2147483648
// 	// int pid;
// 	// int	pipe2[2];
// 	int fd;
// 	// pipe(pipe2);
// 	// fd = open("hi", O_RDWR | O_TRUNC);
// 	// write(fd, "asd\n", 4);
// 	// write(fd, "asa\n", 4);
// 	// for(int i = 0; 1; i++)
// 	// char line[10];
// 	// {
// 	// write(pipe2[1], "hello\n", 7);
// 	// pid = fork();
// 	// if (pid == 0)
// 	// {
// 	// 	// dup2(fd, STDIN_FILENO);
// 	// 	// close(fd);
// 	// 	close(pipe2[1]);
// 	// 	dup2(pipe2[0], STDIN_FILENO);
// 	// 	close(pipe2[0]);
// 	// 	execve(path, cmd, env);
// 	// 	printf("error\n");
// 	// 	exit(1);
// 	// }

// 	// sleep(2);
// 	// write(pipe2[1], "world\n", 7);
// 	// pid = fork();
// 	// if (pid == 0)
// 	// {
// 	// 	// dup2(fd, STDIN_FILENO);
// 	// 	// close(fd);
// 	// 	close(pipe2[1]);
// 	// 	dup2(pipe2[0], STDIN_FILENO);
// 	// 	close(pipe2[0]);
// 	// 	execve(path, cmd, env);
// 	// 	printf("error\n");
// 	// 	exit(1);
// 	// }
// 	// close(pipe2[1]);
// 	// waitpid(pid, NULL, 0);
// 	// printf("parent: %s", line);
// 	// line[9] = '\0';
// 	// printf("parent: %s", line);

// 	// }
// 	// char *temp = *cmd;
// 	// cmd++;
// 	// free(temp);
// 	// print_array(cmd);

// 	// printf("%d\n", execve(path, argv, env));
// 	// chdir("/Users/jmolenaa/Codam/Codam_unfinished/minihell/minishell/incs");
// 	execve(path, cmd, env);
// 	// printf("%d\n", errno);
// 	// perror("hi");
// }
