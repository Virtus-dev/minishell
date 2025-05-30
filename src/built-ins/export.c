/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:55:05 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/13 16:33:46 by fracurul         ###   ########.fr       */
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
void	ft_export(t_data *data, char **splited, int i)
{
	if (!data->argv[1])
	{
		ft_print_map(data, data->exp);
		return ;
	}
	while (data->argv[++i])
	{
		splited = ft_mini_split(data->argv[i], '=');
		if (ft_check_expformat(splited[0]))
		{
			if (ft_strchr(data->argv[i], '='))
			{
				ft_mapcmp_update(data->exp, data->argv[i]);
				ft_mapcmp_update(data->env, data->argv[i]);
			}
			else
				ft_mapcmp_update(data->exp, data->argv[i]);
		}
		else
		{
			ft_putstr_fd("export: not a valid identifier: ", STDERR_FILENO);
			ft_putendl_fd(data->argv[i], STDERR_FILENO);
		}
		ft_free_matrix(splited);
	}
}
