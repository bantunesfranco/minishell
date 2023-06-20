/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 14:51:40 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/20 18:59:11 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

	// #include "structs.h"
#include "parsing.h"
#include "expander.h"
#include "minishell.h"
#include "libft.h"

size_t	find_end_of_var(char *word, size_t start_of_var)
{
	if (*(word + start_of_var) == '?')
		return (start_of_var + 1);
	// if (ft_isdigit(*(word + start_of_var)))
	// 	return (start_of_var);
	while (ft_isalnum(*(word + start_of_var)) || *(word + start_of_var) == '_')
		start_of_var++;
	return (start_of_var);
}

char	*compare_with_env(char *var_name, t_gen *gen)
{
	int	i;

	i = 0;
	// (void)len;
	if (*var_name == '?')
		return (ft_itoa(gen->status));
	while (*(gen->env + i))
	{
		// printf("%s\n", var_name);
		// printf("%s\n", *(gen->env + i));
		if (!ft_envcmp(var_name, *(gen->env + i)))
			return (ft_strdup(*(gen->env + i) + ft_strlen(var_name)));
		i++;
	}
	return (ft_strdup(""));
}

char	*get_var_name(char *word, int len)
{
	char	*temp;
	char	*var_name;

	temp = ft_substr(word, 0, len);
	if (temp == NULL)
		err_msg(NULL, "expander");
	var_name = ft_strjoin(temp, "=");
	if (var_name == NULL)
		err_msg(NULL, "expander");
	free(temp);
	return (var_name);
}

char	*expand_str_with_var_value(char *var_value, char **word, int start_of_var, int end_of_var)
{
	char	*new_str;
	char	*temp;

	// printf("%zu %s\n", ft_strlen(var_value), var_value);
	// printf("%zu %s\n", ft_strlen(*word), *word);
	new_str = ft_substr(*word, 0, start_of_var - 1);
	if (new_str == NULL)
		err_msg(NULL, "expander");
	// printf("%zu %s\n", ft_strlen(new_str), new_str);
	temp = ft_strjoin_free(new_str, var_value);
	if (temp == NULL)
		err_msg(NULL, "expander");
	// printf("%zu %s\n", ft_strlen(temp), temp);
	new_str = ft_strjoin(temp, *word + end_of_var);
	if (new_str == NULL)
		err_msg(NULL, "expander");
	// printf("%zu %s\n", ft_strlen(new_str), new_str);
	free(temp);
	free(*word);
	return (new_str);
}

size_t	expand_variable(char **word, size_t start_of_var, t_gen *gen)
{
	size_t	end_of_var;
	char	*var_value;
	char	*var_name;
	size_t	return_value;

	end_of_var = find_end_of_var(*word, start_of_var);
	if (end_of_var == start_of_var)
		return (start_of_var);
	var_name = get_var_name(*word + start_of_var, end_of_var - start_of_var);
	// printf("%s\n", var_name);
	var_value = compare_with_env(var_name, gen);
	return_value = start_of_var + ft_strlen(var_value) - 1;
	free(var_name);
	// var = NULL;
	// *var = '\0';
	*word = expand_str_with_var_value(var_value, word, start_of_var, end_of_var);
	// free(var_value);
	// printf("%s\n", var_value);
	// printf("%s\n", *word);
	// printf("%zd %zd\n",return_value, start_of_var);
	// printf("%c\n", *(*word + return_value));
	return (return_value);
}

char	*expand_environment_vars(char *word, t_gen *gen, int heredoc, t_quote_mark **head)
{
	size_t	i;
	int		double_quoted;

	i = 0;
	double_quoted = 0;
	// printf("hi\n");
	while (*(word + i) != '\0')
	{
		if (*(word + i) == '$')
		{
			i = expand_variable(&word, i + 1, gen);
			continue ;
			// printf("%zu\n", i);
			// printf("%c\n", *(word + i));
		}
		if (*(word + i) == '\'' && heredoc == 0 && double_quoted == 0)
		{
			// printf("%c\n", *(word + i));
			i = handle_quotes(word, i, head);
			// i = skip_quotes(word, i);
			// printf("%c\n", *(word + i));
		}
		if (*(word + i) == '"' && heredoc == 0)
		{
			i = handle_quotes(word, i, head);
			double_quoted = (double_quoted + 1) % 2;
		}
		// if (*(word + i) == '\0')
		// 	break ;
		// printf("%d\n", *(word + i));
		i++;
	}
	return (word);
}
