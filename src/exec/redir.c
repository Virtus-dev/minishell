/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:13:55 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/01 12:52:19 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_redi(t_data *data)
{
	char	**split;
	int		i;
	int		type;

	split = ft_split(data->input, ' ');
	i = 0;
	while (split[i])
	{
		if (ft_is_sout(split[i]) || ft_is_dout(split[i]))
		{
			type = ft_rediout_type(split[i]);
			if (split[i + 1])
				ft_redirout(data, split[i + 1], type);
		}
		else if (ft_is_sin(split[i]) || ft_is_din(split[i]))
		{
			type = ft_redin_type(split[i]);
			printf("split[%d] = %s, redir_type = %d\n",i, split[i], type);
			if (split[i + 1])
				ft_redirin(data, split[i + 1], type);
		}
		i++;
	}
	ft_free_matrix(split);
}
