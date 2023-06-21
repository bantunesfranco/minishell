/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 14:05:12 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/21 10:59:29 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "structs.h"
# include "stdlib.h"
# include <stdbool.h>

typedef struct s_quote_mark
{
	size_t				word_index;
	size_t				array_index;
	size_t				word_index_2;
	struct s_quote_mark	*next;
}						t_quote_mark;

void	expand_pipeline(t_cmd *cmd, t_gen *gen);
bool	expand_redirect(char **name, t_gen *gen);
void	free_quote_list(t_quote_mark *head);
char	*expand_environment_vars(char *word, t_gen *gen, int heredoc, t_quote_mark **head);
char	**word_splitting(char *str, t_quote_mark *head);
size_t	handle_quotes(char *word, size_t i, t_quote_mark **head);
size_t	skip_quotes_if_neccesarry(size_t i, t_quote_mark **head);
void	quote_removal(char **split_word, t_quote_mark *head);

#endif
