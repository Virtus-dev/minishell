/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:59:39 by fracurul          #+#    #+#             */
/*   Updated: 2025/04/17 16:00:01 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

t_token	**tokenize_command(char **tokens)
{
	t_token	**cmds;
	int		i;
	int		cmdi;
	int		argi;

	cmds = (t_token **)ft_calloc(20, sizeof(t_token *));
	i = 0;
	cmdi = 0;
	while (tokens[i])
	{
		argi = 0;
		cmds[cmdi] = ft_calloc(1, sizeof(t_token));
		cmds[cmdi]->cmd = ft_strdup(tokens[i++]);
		cmds[cmdi]->cargs = ft_calloc(20, sizeof(char *));
		while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
			cmds[cmdi]->cargs[argi++] = ft_strdup(tokens[i++]);
		if (tokens[i] && !ft_strcmp(tokens[i], "|"))
			i++;
		cmdi++;
	}
	cmds[cmdi] = NULL;
	return (cmds);
}
