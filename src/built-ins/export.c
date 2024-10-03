/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:55:05 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/28 18:11:02 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	i = 2;
	if (!data->argv[i])
		ft_print_map(data, data->exp);
	else
	{
		while (data->argv[i])
		{
			splited = ft_mini_split(data->argv[i], '=');
			if (!ft_check_expformat(splited[0]))
				i++;
			else
			{
				if (ft_strchr(data->argv[i], '='))
				{
					if (ft_key_exist(data->exp, splited[0]))
						ft_mapcmp_update(data->exp, data->argv[i]);
					ft_mapcmp_update(data->env, data->argv[i]);
				}
				else
					ft_mapcmp_update(data->exp, data->argv[i]);
				i++;
			}
		free(splited);
		}
	}
}