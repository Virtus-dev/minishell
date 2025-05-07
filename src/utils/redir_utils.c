/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:43:09 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/07 18:25:37 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_clean_redirections(char **tokens)
{
	char	**cleaned;
	int		i;
	int		j;
	int		type;

	i = 0;
	j = 0;
	cleaned = ft_calloc(sizeof(char *), (ft_matrix_size(tokens) + 1));
	if (!cleaned)
		return (NULL);
	while (tokens[i])
	{
		type = ft_redir_type(tokens[i]);
		if ((type == S_OUT || type == D_OUT || type == S_IN || type == D_IN)
			&& tokens[i + 1])
		{
			i += 2;
			continue ;
		}
		cleaned[j++] = ft_strdup(tokens[i++]);
	}
	return (cleaned);
}

void	ft_clean_and_replace_args(t_data *data)
{
	char	**cleaned;

	cleaned = ft_clean_redirections(data->argv);
	ft_free_matrix(data->argv);
	data->argv = cleaned;
}

int	ft_redi_ok(const char *input)
{
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	dquote = 0;
	squote = 0;
	while (input[i])
	{
		if (input[i] == '"' && !squote)
			dquote = !dquote;
		else if (input[i] == '\'' && !dquote)
			squote = !squote;
		else if (!dquote && !squote && (input[i] == '>' || input[i] == '<'))
		{
			if ((input[i] == '>' && input[i + 1] == '>')
				|| (input[i] == '<' && input[i + 1] == '<'))
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}
