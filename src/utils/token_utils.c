/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:57:01 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/19 16:00:14 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_toklen(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

int	ft_matrix_size(char **matrix)
{
	int	i;

	if (!matrix)
		return (0);
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	i = -1;
	if (!tokens)
	{
		perror(TOK_ERR);
		return ;
	}
	while (tokens[++i])
	{
		if (tokens[i]->cmd)
		{
			free(tokens[i]->cmd);
			tokens[i]->cmd = NULL;
		}
		if (tokens[i]->cargs)
		{
			ft_free_matrix(tokens[i]->cargs);
			tokens[i]->cargs = NULL;
		}
		free(tokens[i]);
		tokens[i] = NULL;
	}
	free(tokens);
}

char	*wrap_export_input(const char *input, int start, char *str)
{
	char	*pre;
	char	*quoted;
	char	*join;
	int		i;

	i = start - 2;
	while (i > 0 && input[i - 1] != ' ' && !is_op(input[i - 1]))
		i--;
	pre = ft_substr(input, i, start - i - 1);
	if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
		quoted = ft_strdup(str);
	else
		quoted = ft_wrap_quotes(str, '"');
	join = ft_strjoin(pre, quoted);
	free(pre);
	free(quoted);
	return (join);
}
