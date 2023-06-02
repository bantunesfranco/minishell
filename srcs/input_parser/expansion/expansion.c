/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 14:51:40 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/02 14:48:32 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing.h"

size_t	skip_quotes(char *line, size_t i)
{
	char	c;

	c = *(line + i);
	i++;
	while (*(line + i) != c && *(line + i) != '\0')
		i++;
	return (i);
}

size_t	skip_to_end(char *word, size_t start_of_var)
{
	while (*(word + start_of_var) != '\0')
}

size_t	expand_variable(char *word, size_t start_of_var, t_gen *gen)
{
	size_t	end_of_var;

	end_of_var = skip_to_end(word, start_of_var);
}

void	expand_environment_vars(char *word, t_gen *gen)
{
	(void)word;
	(void)gen;
	size_t	i;

	i = 0;
	while (*(word + i) != '\0')
	{
		if (*(word + i) == '$')
			i = expand_variable(word, i, gen);
		if (*(word + i) == '\'')
			i = skip_quotes(word, i);
		i++;
	}
	printf("\n");
}
