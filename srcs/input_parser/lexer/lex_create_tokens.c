/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_create_tokens.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 10:44:46 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/04 10:10:51 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "minishell.h"

static t_token_type	get_token_type(char *line, t_par_info *p_info)
{
	int		i;

	i = 0;
	while (*(p_info->token_array + i) != NULL)
	{
		if (!ft_strncmp(*(p_info->token_array + i), line, \
			ft_strlen(*(p_info->token_array + i))))
			return (i);
		i++;
	}
	return (i);
}

static t_token	*create_token_node(char *line, t_token_type new_token_type, \
									t_par_info *p_info)
{
	t_token	*new_token;
	char	*new_word;

	new_word = create_word(line, new_token_type, p_info);
	if (new_word == NULL)
		err_msg(NULL, "parser");
	new_token = make_new_token(new_word, new_token_type);
	return (new_token);
}

static void	add_token(char **line, t_par_info *p_info, t_token **head)
{
	t_token			*new_token;
	t_token_type	new_token_type;

	new_token_type = get_token_type(*line, p_info);
	if (new_token_type >= 9 && new_token_type <= 10)
		(*line)++;
	else
	{
		new_token = create_token_node(*line, new_token_type, p_info);
		add_new_token_to_back(head, new_token);
		(*line) = *(line) + ft_strlen(new_token->word);
	}
}

static void	add_newline_token(t_token **head)
{
	t_token	*newline_token;
	char	*word;

	word = ft_strdup("newline");
	if (word == NULL)
		err_msg(NULL, "parser");
	newline_token = make_new_token(word, NEW_LINE);
	add_new_token_to_back(head, newline_token);
}

void	create_token_list(char *line, t_par_info *p_info, t_token **head)
{
	*head = NULL;
	while (*line != '\0')
		add_token(&line, p_info, head);
	add_newline_token(head);
}
