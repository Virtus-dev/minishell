/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:13:55 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 15:52:07 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_redi(t_data *data)
{
	int		redir_pos;
	char	**split;
	int		redir_out;
	int		redir_in;

	split = ft_split(data->input, ' ');
	redir_pos = ft_redir_pos(split);
	if (ft_is_sout(split[redir_pos]) || ft_is_dout(split[redir_pos]))
	{
		redir_out = ft_rediout_type(split[redir_pos]);
		if (split[redir_pos + 1] != NULL)
			ft_redirout(data, split[redir_pos + 1], redir_out);
		else
			fprintf(stderr, "Error: NO args for output redirection.\n");
	}
	if (ft_is_sin(split[redir_pos]) || ft_is_din(split[redir_pos]))
	{
		redir_in = ft_redin_type(split[redir_pos]);
		if (split[redir_pos + 1] != NULL)
			ft_redirin(data, split[redir_pos + 1], redir_in);
		else
			fprintf(stderr, "Error: NO args for input redirection.\n");
	}
	ft_free_matrix(split);
}
