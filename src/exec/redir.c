/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:13:55 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/13 13:01:43 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_start_redi(t_data *data)
{
    int     redir_pos;
    char    **split;
    int		redir_out;
	int		redir_in;

    split = ft_split(data->input, ' ');
    redir_pos = ft_redir_pos(split);
	ft_printdbstring(split);
	if (ft_is_sout(split[redir_pos]) || ft_is_dout(split[redir_pos]))
	{
		redir_out = ft_rediout_type(split[redir_pos]);
		if (redir_out == S_OUT)
			printf("REDIRECTION TYPE = '>'\nSplit[%d + 1] = %s\n", redir_pos, split[redir_pos + 1]);
		else
			printf("REDIRECTIOON TYPE = '>>'\n");
		if (split[redir_pos + 1] != NULL)
			ft_redirout(data, split[redir_pos + 1], redir_out);
		else
			fprintf(stderr, "Error: Arguments needed for output redirection.\n");
	}
	if (ft_is_sin(split[redir_pos]) || ft_is_din(split[redir_pos]))
	{
		redir_in = ft_redin_type(split[redir_pos]);
		if (split[redir_pos + 1] != NULL)
			ft_redirin(data, split[redir_pos], redir_in);
		else
			fprintf(stderr, "Error: Arguments needed for input redirection.\n");
	}
	ft_free_matrix(split);
}