/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:57:01 by arigonza          #+#    #+#             */
/*   Updated: 2024/11/10 13:31:20 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	ft_freetok(t_token **token)
{
    int i;

    i = 0;
    while (token[i])
        free(token[i++]);
    free(token);
}
*/

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
	return(i);
}