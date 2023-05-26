/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:20:03 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/26 19:42:03 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing_structs.h"

void	print_token(t_token_type type, char *word)
{
	if (type == PIPE)
		printf("PIPE				%s\n", word);
	else if (type == PIPE_PIPE)
		printf("PIPE_PIPE			%s\n", word);
	else if (type == AMPERSAND_AMPERSAND)
		printf("AMPERSAND_AMPERSAND		%s\n", word);
	else if (type == OPEN_PAR)
		printf("OPEN_PAR			%s\n", word);
	else if (type == CLOSE_PAR)
		printf("CLOSE_PAR			%s\n", word);
	else if (type == LESS)
		printf("LESS				%s\n", word);
	else if (type == LESS_LESS)
		printf("LESS_LESS			%s\n", word);
	else if (type == GREAT)
		printf("GREAT				%s\n", word);
	else if (type == GREAT_GREAT)
		printf("GREAT_GREAT			%s\n", word);
	else if (type == SPACE_)
		printf("SPACE				[%s]\n", word);
	else if (type == TAB_)
		printf("TAB			[%s]\n", word);
	else if (type == NEW_LINE)
		printf("NEW_LINE			[%s]\n", word);
	else if (type == CHARACTERS)
		printf("WORD				%s\n", word);
	else
		printf("somethings wrong	\n");
}

void	print_tokens(t_token *first_token)
{
	t_token	*temp;

	temp = first_token;
	while (temp != NULL)
	{
		print_token(temp->type, temp->word);
		temp = temp->next;
	}
}

void	print_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	print_redirects(t_pipeline *first_pipeline)
{
	t_redirect	*temp_input;
	t_redirect	*temp_output;

	if (first_pipeline->first_cmd == NULL)
		return ;
	temp_input = first_pipeline->first_cmd->input;
	temp_output = first_pipeline->first_cmd->output;
	printf("INPUTS\n");
	while (temp_input != NULL)
	{
		if (temp_input->type == 0)
			printf("%s",  "<<");
		else if (temp_input->type == 1)
			printf("%s",  "<");
		else
			printf("wrong");
		printf(" %s, ", temp_input->name);
		temp_input = temp_input->next;
	}
	printf("\nOUTPUTS\n");
	while (temp_output != NULL)
	{
		if (temp_output->type == 2)
			printf("%s",  ">>");
		else if (temp_output->type == 3)
			printf("%s",  ">");
		else
			printf("wrong");
		printf(" %s, ", temp_output->name);
		temp_output = temp_output->next;
	}
}

void	free_cmds(t_pipeline *first_pipeline)
{
	t_pipeline	*temp;
	t_pipeline	*temp_1;
	t_cmd		*temp_cmd;
	t_cmd		*temp_cmd_1;
	t_redirect	*temp_redirect;
	t_redirect	*temp_redirect_1;

	temp = first_pipeline;
	while (temp != NULL)
	{
		temp_cmd = temp->first_cmd;
		while (temp_cmd != NULL)
		{
			temp_redirect = temp_cmd->input;
			while (temp_redirect != NULL)
			{
				temp_redirect_1 = temp_redirect;
				temp_redirect = temp_redirect->next;
				free(temp_redirect_1->name);
				free(temp_redirect_1);
			}
			temp_redirect = temp_cmd->output;
			while (temp_redirect != NULL)
			{
				temp_redirect_1 = temp_redirect;
				temp_redirect = temp_redirect->next;
				free(temp_redirect_1->name);
				free(temp_redirect_1);
			}
			temp_cmd_1 = temp_cmd;
			temp_cmd = temp_cmd->next;
			free(temp_cmd_1);
		}
		temp_1 = temp;
		temp = temp->next;
		free(temp_1);
	}
}

void	print_commands(t_pipeline *first_pipeline)
{
	t_pipeline	*temp;
	t_cmd		*temp_cmd;

	temp = first_pipeline;
	while (temp != NULL)
	{
		printf("nex pipeline : \n");
		temp_cmd = temp->first_cmd;
		if (temp_cmd == NULL)
			printf("no cmd\n");
		else
		{
			while (temp_cmd != NULL)
			{
				printf("next simple cmd : \n");
				print_array(temp_cmd->cmd);
				temp_cmd = temp_cmd->next;
			}
		}
		temp = temp->next;
	}
}
