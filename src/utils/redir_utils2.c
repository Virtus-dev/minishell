/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:43:09 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 16:23:13 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_clean_redirections(char **tokens)
{
	char	**cleaned;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cleaned = malloc(sizeof(char *) * (ft_matrix_size(tokens) + 1));
	if (!cleaned)
		return (NULL);
	while (tokens[i])
	{
		if ((ft_rediout_type(tokens[i])
				|| ft_redin_type(tokens[i])) && tokens[i + 1])
		{
			i += 2;
			continue ;
		}
		cleaned[j++] = ft_strdup(tokens[i++]);
	}
	cleaned[j] = NULL;
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

int	ft_redin_type(char *str)
{
	if (ft_is_sin(str))
		return (S_IN);
	else if (ft_is_din(str))
		return (D_IN);
	return (0);
}

int	ft_redir_pos(char **argv)
{
	int	i;

	if (!argv)
		return (perror(ARG_ERR), FALSE);
	i = 0;
	while (argv[i])
	{
		if (ft_is_sout(argv[i]) || ft_is_dout(argv[i])
			|| ft_is_sin(argv[i]) || ft_is_din(argv[i]))
			return (i);
		i++;
	}
	return (FALSE);
}
