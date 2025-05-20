/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:59:39 by fracurul          #+#    #+#             */
/*   Updated: 2025/05/20 13:18:12 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '"' || c == '\'');
}

int	export_quoted_input(char *token)
{
	char	*equal;
	char	*dquote;
	int		len;

	len = ft_strlen(token);
	if (!token)
		return (0);
	equal = ft_strchr(token, '=');
	if (!equal)
		return (0);
	dquote = ft_strchr(equal + 1, '"');
	if (dquote && token[len - 1] == '"')
		return (1);
	return (0);
}

t_token	**tokenize_command(char **tokens, int *pos, int i, int cmdi)
{
	t_token	**cmds;
	int		argi;

	cmds = (t_token **)ft_calloc(*pos + 1, sizeof(t_token *));
	while (tokens[i])
	{
		argi = 0;
		cmds[cmdi] = ft_calloc(*pos, sizeof(t_token));
		cmds[cmdi]->cmd = ft_strdup(tokens[i++]);
		cmds[cmdi]->cargs = ft_calloc(*pos, sizeof(char *));
		while (tokens[i] && (ft_strcmp(tokens[i], "|") != 0))
		{
			if (export_quoted_input(tokens[i]))
				cmds[cmdi]->cargs[argi] = ft_strdup(tokens[i++]);
			else
				cmds[cmdi]->cargs[argi++] = ft_strdup(tokens[i++]);
		}
		if (tokens[i] && !ft_strcmp(tokens[i], "|"))
			i++;
		cmdi++;
	}
	ft_free_matrix(tokens);
	return (cmds);
}
