/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:39:10 by fracurul          #+#    #+#             */
/*   Updated: 2025/04/13 14:45:53 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_handler(char **tokens, const char *input, int *i, int j)
{
	char	quote;
	int		start;

	quote = input[(*i)++];
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	tokens[j] = ft_substr(input, start, *i - start);
	if (input[*i])
		(*i)++;
	return (j + 1);
}

static int	op_handler(char **tokens, const char *input, int *i, int j)
{
	int	len;

	len = 1;
	if ((input[*i] == '>' || input[*i] == '<') && input[*i] == input[*i + 1])
		len = 2;
	tokens[j] = ft_substr(input, *i, len);
	*i += len;
	return (j + 1);
}

static int	word_handler(char **tokens, const char *input, int *i, int j)
{
	int	start;

	start = *i;
	while(input[*i] && input[*i] != ' ' && input[*i] != '\t' && !is_op(input[*i]))
		(*i)++;
	tokens[j] = ft_substr(input, start, *i - start);
	return (j + 1);
}

char	**tokenizer(const char *input)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = (char **)ft_calloc(256, sizeof(char *));
	i = 0;
	j = 0;
	while(input[i])
	{
		while(input[i] == ' ' || input[i] == '\t')
			i++;
		if(input[i] == '\'' || input[i] == '\"')
			j = quotes_handler(tokens, input, &i, j);
		else if(is_op(input[i]))
			j = op_handler(tokens, input, &i, j);
		else
			j = word_handler(tokens, input, &i, j);
	}
	tokens[j] = NULL;
	return (tokens);
}
