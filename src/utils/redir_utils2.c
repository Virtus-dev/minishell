/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:43:09 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/13 15:58:46 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_clean_redirections(char **tokens)
{
	char	**cleaned;
	int		i = 0, j = 0;

	cleaned = malloc(sizeof(char *) * (ft_matrix_size(tokens) + 1));
	if (!cleaned)
		return (NULL);

	while (tokens[i])
	{
		if ((ft_rediout_type(tokens[i]) || ft_redin_type(tokens[i])) && tokens[i + 1])
		{
			i += 2;
			continue;
		}
		cleaned[j++] = ft_strdup(tokens[i++]);
	}
	cleaned[j] = NULL;
	return (cleaned);
}

void	ft_clean_and_replace_args(t_data *data)
{
	char **cleaned;
    
    cleaned = ft_clean_redirections(data->argv);
	ft_free_matrix(data->argv);
	data->argv = cleaned;
}
