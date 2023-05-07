/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/03 10:59:54 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"

void	add_token_to_back(t_token **first_token, t_token *new_token)
{
	t_token	*temp;

	temp = *first_token;
	if (temp == NULL)
		*first_token = new_token;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
		new_token->prev = temp;
	}
}

t_token	*make_new_token(char *word, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->word = word;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	setup_array(char *token_array[7])
{
	token_array[0] = "|";
	token_array[1] = ">";
	token_array[2] = "<";
	token_array[3] = "&";
	token_array[4] = " \t";
	token_array[5] = "\n";
	token_array[6] = NULL;
}

t_token_type	get_token_type(char *line)
{
	char	*token_array[7];
	int		i;

	i = 0;
	setup_array(token_array);
	while (*(token_array + i) != NULL)
	{
		if (ft_strchr(*(token_array + i), *line))
			return (i);
		i++;
	}
	return (i);
}

void	setup_meta_characters(char meta_characters[8])
{
	meta_characters[0] = '|';
	meta_characters[1] = '<';
	meta_characters[2] = '>';
	meta_characters[3] = '&';
	meta_characters[4] = ' ';
	meta_characters[5] = '\t';
	meta_characters[6] = '\n';
	meta_characters[7] = '\0';
}

size_t	skip_quotes(char *line, size_t i)
{
	char	c;

	c = *(line + i);
	i++;
	while (*(line + i) != c && *(line + i) != '\0')
		i++;
	return (i);
}

char	*create_word(char *line)
{
	size_t	i;
	char	meta_characters[8];

	setup_meta_characters(meta_characters);
	i = 0;
	while (ft_strchr(meta_characters, *(line + i)) == NULL)
	{
		if (*(line + i) == '\'' || *(line + i) == '"')
			i = skip_quotes(line, i);
		if (*(line + i) == '\0')
			break ;
		i++;
	}
	return (ft_substr(line, 0, i));
}

t_token	*create_token(char *line, t_token_type new_token_type)
{
	t_token *new_token;
	char	*new_word;

	new_word = NULL;
	if (new_token_type == WORD)
	{
		new_word = create_word(line);
		if (new_word == NULL)
			return (NULL);
	}
	new_token = make_new_token(new_word, new_token_type);
	return (new_token);
}

void	skip_token(char **line, char *new_word)
{
	if (new_word == NULL)
		(*line)++;
	else
		(*line) = *(line) + ft_strlen(new_word);
}

void	tokenize(char **line, t_token **first_token)
{
	t_token			*new_token;
	t_token_type	new_token_type;

	new_token_type = get_token_type(*line);
	new_token = create_token(*line, new_token_type);
	if (new_token == NULL)
		exit(1);			//change later to some malloc failure function
	add_token_to_back(first_token, new_token);
	skip_token(line, new_token->word);
}

t_token	*lexer(char *line)
{
	t_token	*first_token;
	int		i;

	first_token = NULL;
	i = 0;
	while (*(line + i) != '\0')
	{
		tokenize(&line, &first_token);
	}
	print_tokens(first_token);
	return (first_token);
}

t_cmd	*parse_line(char *line)
{
	t_cmd	*first_cmd;
	t_token	*first_token;

	first_cmd = NULL;
	first_token = lexer(line);
	return (first_cmd);
}
