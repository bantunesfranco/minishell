/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/10 20:16:58 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"

t_token_type	get_token_type(char *line, t_parsing_info *p_info)
{
	char	*token_array[7];
	int		i;

	i = 0;
	while (*(p_info->token_array + i) != NULL)
	{
		if (!ft_strncmp(*(token_array + i), line, ft_strlen(*(token_array + i))))
			return (i);
		i++;
	}
	return (i);
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

char	*create_word(char *line, t_parsing_info *p_info)
{
	size_t	i;

	i = 0;
	while (ft_strchr(p_info->metacharacters, *(line + i)) == NULL)
	{
		if (*(line + i) == '&' && *(line + i + 1) == '&')
			break ;
		if (*(line + i) == '\'' || *(line + i) == '"')
			i = skip_quotes(line, i);
		if (*(line + i) == '\0')
			break ;
		i++;
	}
	return (ft_substr(line, 0, i));
}

t_token	*create_token(char *line, t_token_type new_token_type, t_parsing_info *p_info)
{
	t_token *new_token;
	char	*new_word;

	new_word = NULL;
	if (new_token_type == WORD)
		new_word = create_word(line, p_info);
	else
		new_word = ft_strdup(*(p_info->token_array) + new_token_type);
	if (new_word == NULL)
			return (NULL);
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

void	tokenize(char **line, t_token **first_token, t_parsing_info *p_info)
{
	t_token			*new_token;
	t_token_type	new_token_type;

	new_token_type = get_token_type(*line, p_info);
	new_token = create_token(*line, new_token_type, p_info);
	if (new_token == NULL)
		exit(1);			//change later to some malloc failure function
	add_token_to_back(first_token, new_token);
	skip_token(line, new_token->word);
}

t_token	*lexer(char *line, t_parsing_info *p_info)
{
	t_token	*first_token;
	int		i;

	first_token = NULL;
	i = 0;
	while (*(line + i) != '\0')
	{
		tokenize(&line, &first_token, p_info);
	}
	print_tokens(first_token);
	return (first_token);
}

t_cmd_list	*parse_line(char *line)
{
	t_cmd_list		*first_cmd;
	t_token			*first_token;
	t_parsing_info	p_info;

	// (void)line;
	// (void)first_token;
	init_struct(&p_info);
	// printf("%s\n", p_info.metacharacters);
	// print_array(p_info.token_array);
	first_cmd = NULL;
	first_token = lexer(line, &p_info);
	return (first_cmd);
}
