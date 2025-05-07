/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:59:39 by fracurul          #+#    #+#             */
/*   Updated: 2025/05/07 18:07:00 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

t_token	**tokenize_command(char **tokens, int *pos)
{
	t_token	**cmds;
	int		i;
	int		cmdi;
	int		argi;

	cmds = (t_token **)ft_calloc(*pos + 1, sizeof(t_token *));
	i = 0;
	cmdi = 0;
	while (tokens[i])
	{
		argi = 0;
		cmds[cmdi] = ft_calloc(1, sizeof(t_token));
		cmds[cmdi]->cmd = ft_strdup(tokens[i++]);
		cmds[cmdi]->cargs = ft_calloc(*pos, sizeof(char *));
		while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
			cmds[cmdi]->cargs[argi++] = ft_strdup(tokens[i++]);
		if (tokens[i] && !ft_strcmp(tokens[i], "|"))
			i++;
		cmdi++;
	}
	ft_free_matrix(tokens);
	return (cmds);
}
