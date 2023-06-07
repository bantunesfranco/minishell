/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 14:51:40 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/07 16:27:00 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

	// #include "structs.h"
	// #include "libft.h"
	// #include "parsing.h"
#include "minishell.h"

static size_t	skip_quotes(char *line, size_t i)
{
	char	c;

	c = *(line + i);
	i++;
	while (*(line + i) != c && *(line + i) != '\0')
		i++;
	return (i);
}

size_t	skip_to_end_of_var(char *word, size_t start_of_var)
{
	while (ft_isalnum(*(word + start_of_var)) || *(word + start_of_var) == '_')
		start_of_var++;
	return (start_of_var);
}

char	*compare_with_env(char *word, t_gen *gen)
{
	int	i;

	i = 0;
	if (*word == '?')
		return (ft_itoa(gen->status));
	while (*(gen->env + i))
	{
		printf("%s\n", word);
		printf("%s\n", *(gen->env + i));
		if (!ft_envcmp(word, *(gen->env + i)))
			return (ft_strdup(*(gen->env + i)));
		i++;
	}
	return (NULL);
}

size_t	expand_variable(char *word, size_t start_of_var, t_gen *gen)
{
	size_t	end_of_var;
	char	*var;

	(void)gen;
	end_of_var = skip_to_end_of_var(word, start_of_var);
	var = compare_with_env(word + start_of_var, gen);
	// var = NULL;
	// *var = '\0';
	printf("%s\n", var);
	return (0);
}

void	expand_environment_vars(char *word, t_gen *gen)
{
	(void)word;
	(void)gen;
	size_t	i;

	i = 0;
	// printf("hi\n");
	while (*(word + i) != '\0')
	{
		if (*(word + i) == '$')
			i = expand_variable(word, i + 1, gen);
		if (*(word + i) == '\'')
			i = skip_quotes(word, i);
		i++;
	}
	printf("%s\n", word);
	printf("\n");
}
