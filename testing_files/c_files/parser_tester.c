/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_tester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 10:47:26 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/06 15:36:36 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "lexer.h"

void	check_operator_parsing(t_pipeline *first_pipeline)
{
	t_pipeline *temp; 
	t_pipeline *temp2; 

	temp = first_pipeline;
	if (temp->prev_control_operator != START)
	{
		printf("error with start operator\n");
		exit(1);
	}
	while (temp->next != NULL)
	{
		// printf("next\n");
		// printf("%d\n", temp->prev_control_operator);
		// printf("%d\n", temp->next_control_operator);
		// printf("%p\n", temp->next);
		// printf("%p\n", temp->prev);
		// printf("%p\n", temp->subshell);
		// if (temp->subshell != NULL)
		// {
		// 	printf("subshell\n");
		// 	printf("%d\n", temp->subshell->open_close);
		// 	printf("%d\n", temp->subshell->pipe_input);
		// 	printf("%d\n", temp->subshell->pipe_output);
		// }
		temp2 = temp;
		temp = temp->next;
		if (temp2->next_control_operator != temp->prev_control_operator)
		{
			printf("error, netx and prev are different\n");
			exit(1);
		}
	}
	if (temp->next_control_operator != END)
	{
		printf("error with end operator\n");
		exit(1);
	}
}

// t_token	*skip_to_close_parenthesis(t_token *open_par)
// {
// 	t_token	*temp;
// 	int		currently_open;

// 	currently_open = 1;
// 	temp = open_par;
// 	while (currently_open > 0)
// 	{
// 		temp = temp->next;
// 		if (temp->type == OPEN_PAR)
// 			currently_open++;
// 		else if (temp->type == CLOSE_PAR)
// 			currently_open--;
// 	}
// 	return (temp);
// }

// void	check_subshell_piping(char *arg, t_pipeline *first_pipeline)
// {
// 	t_pipeline *temp; 
// 	t_pipeline *temp2; 

// 	temp = first_pipeline;
// 	while (temp->next != NULL)
// 	{
// 		if (temp->subshell != NULL)
// 		{
// 			if (temp->subshell->open_close == CLOSE)
// 				continue ;
// 		}
// 		temp = temp->next;
// 	}
// }

void	print_redirect(t_redirect *redirect)
{
	if (redirect->name == NULL)
		return ;
	while (redirect != NULL)
	{
		if (redirect->type == 0)
			printf(" %s",  "<<");
		else if (redirect->type == 1)
			printf(" %s",  "<");
		else if (redirect->type == 2)
			printf(" %s",  ">>");
		else if (redirect->type == 3)
			printf(" %s",  ">");
		else
			printf("wrong");
		// if (redirect->name != NULL)
			printf(" %s", redirect->name);

		// if (redirect->name == NULL && redirect->type == INPUT)
		// 	printf(" 0");
		// else if (redirect->name == NULL && redirect->type == OUTPUT)
		// 	printf(" 1");
		// else
		redirect = redirect->next;
	}
}

void	print_cmd_array(char	**cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
	{
		// printf(" none");
		return ;
	}
	while (*(cmd + i) != NULL)
	{
		printf(" %s", *(cmd + i));
		i++;
	}
}

void	print_cmd(t_cmd *first_cmd)
{
	t_cmd	*temp;

	temp = first_cmd;
	while (temp != NULL)
	{
		print_cmd_array(temp->cmd);
		print_redirect(temp->input);
		print_redirect(temp->output);
		temp = temp->next;
		if (temp != NULL)
			printf(" |");
	}
}

void	print_control_operator(t_control_operator type)
{
	if (type == OR)
		printf(" ||");
	if (type == PIPELINE)
		printf(" |");
	if (type == AND)
		printf(" &&");

}

void	print_parsed_struct(t_pipeline *first_pipeline)
{
	t_pipeline *temp;

	printf("start:");
	temp = first_pipeline;
	while (temp != NULL)
	{
		// dprintf(2, "%p\n", temp->subshell);
		// if (temp->subshell != NULL)
		// 	dprintf(2, "%d\n", temp->subshell->open_close);
		if (temp->subshell != NULL && temp->subshell->open_close == OPEN)
		{
			printf(" ( - %d %d", temp->subshell->pipe_input, temp->subshell->pipe_output);
			print_redirect(temp->subshell->input);
			print_redirect(temp->subshell->output);
		}
		else if (temp->subshell != NULL && temp->subshell->open_close == CLOSE)
		{
			// dprintf(2, "huh\n");
			printf(" )");
		}
		else
		{
			print_cmd(temp->first_cmd);
			print_control_operator(temp->next_control_operator);
		}
		temp = temp->next;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	t_pipeline	*first_pipeline;
	t_gen	gen;
	char	**start_env;

	start_env = ft_arrdup(envp);
	gen.env = env_init(start_env);
	first_pipeline = parse_line(argv[1], &gen);
	if (first_pipeline == NULL)
		return (0);
	check_operator_parsing(first_pipeline);
	print_parsed_struct(first_pipeline);
}
