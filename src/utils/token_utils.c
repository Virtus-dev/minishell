/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:57:01 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 17:30:29 by fracurul         ###   ########.fr       */
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
		if (tokens[i]->cargs[0] && tokens[i]->cargs)
		{
			ft_free_matrix(tokens[i]->cargs);
			tokens[i]->cargs = NULL;
		}
		free(tokens[i]);
		tokens[i] = NULL;
	}
	free(tokens);
	tokens = NULL;
}
