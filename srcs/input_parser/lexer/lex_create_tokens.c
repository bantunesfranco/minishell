/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_create_tokens.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 10:44:46 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/29 13:23:38 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "minishell.h"

/*	gets the type of token. Loops through our double array and compares the strings to where we are in the line
	returns the index of the string we found which corresponds to the correct tokentype in our enum */

static t_token_type	get_token_type(char *line, t_parsing_info *p_info)
{
	int		i;

	i = 0;
	while (*(p_info->token_array + i) != NULL)
	{
		if (!ft_strncmp(*(p_info->token_array + i), line, ft_strlen(*(p_info->token_array + i))))
			return (i);
		i++;
	}
	return (i);
}

/*	makes a new node for out list. first it mallocs the word corresponding to our token.
	then it creates the node with the created word and the token type
	returns an allocated node with an allocated word in it */

static t_token	*create_token_node(char *line, t_token_type new_token_type, t_parsing_info *p_info)
{
	t_token	*new_token;
	char	*new_word;

	new_word = create_word(line, new_token_type, p_info);
	if (new_word == NULL)
		err_msg(NULL, "parser");
	new_token = make_new_token(new_word, new_token_type);
	return (new_token);
}

/*	gets the token type we're dealing with, then creates the token node
	then adds the newly created token to our list and at the end skips over our token in the line
	adjusts the pointer to the line
	if the token is a whitespace we skip the creation of the token */

static void	add_token(char **line, t_parsing_info *p_info, t_token **first_token)
{
	t_token			*new_token;
	t_token_type	new_token_type;

	new_token_type = get_token_type(*line, p_info);
	if (new_token_type >= 9 && new_token_type <= 10)
		(*line)++;
	else
	{
		new_token = create_token_node(*line, new_token_type, p_info);
		add_new_token_to_back(first_token, new_token);
		(*line) = *(line) + ft_strlen(new_token->word);
	}
}

/*	adding newline token to the back of the list*/

static void	add_newline_token(t_token **first_token)
{
	t_token	*newline_token;
	char	*word;

	word = ft_strdup("newline");
	if (word == NULL)
		err_msg(NULL, "parser");
	newline_token = make_new_token(word, NEW_LINE);
	add_new_token_to_back(first_token, newline_token);
}

/*	loops over the given line and creates tokens until we reach the null character
	the result is a list with malloced nodes that have a pointer to a word in them that is also malloced
	needs to be free when lexer is done */

void	create_token_list(char *line, t_parsing_info *p_info, t_token **first_token)
{
	*first_token = NULL;
	while (*line != '\0')
		add_token(&line, p_info, first_token);
	add_newline_token(first_token);
}
