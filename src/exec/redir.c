/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:13:55 by arigonza          #+#    #+#             */
/*   Updated: 2025/03/28 12:22:57 by arigonza         ###   ########.fr       */
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
	if (ft_is_sout(split[redir_pos]) || ft_is_dout(split[redir_pos]))
	{
		redir_out = ft_rediout_type(split[redir_pos]);
		ft_redirout(data, split[redir_pos + 1], redir_out);
	}
	if (ft_is_sin(split[redir_pos]) || ft_is_din(split[redir_pos]))
	{
		redir_in = ft_redin_type(split[redir_pos]);
		ft_redirin(data, split[redir_pos], redir_in);
	}
	ft_free_matrix(split);
}