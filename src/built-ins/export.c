/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:55:05 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/23 16:00:46 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Replicates the 'export' command, wich creates
 *  or modifies enviromental variables.
 * 
 * @param data The structure that contains all the information
 *  we need, such as the arguments passed for the 'export' command.
 */
void	ft_export(t_data *data)
{
	int		i;
	char	**splited;

	i = 0;
	while (data->argv[i])
	{
		splited = ft_split(data->argv[i], '=');
		if (ft_check_expformat(data->argv[i]))
			i++;
		else
		{
			if (ft_strchr(data->argv[i], '='))
			{
				if (data->exp)
					if (ft_key_exist(data->exp, splited[i]))
						ft_mapcmp_update(data->exp, data->argv[i]);
				ft_mapcmp_update(data->env, data->argv[i]);
			}
			else
			{
				if (!ft_key_exist(data->exp, splited[i]) && !ft_key_exist(data->env, splited[i]))
					ft_add_key(data->exp, ft_new_key(splited[i], splited[i + 1]));
			}
			i++;
		}
		free(splited);
	}
}