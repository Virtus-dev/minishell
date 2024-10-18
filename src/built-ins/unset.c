/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:35:25 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/17 12:09:38 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Replicates the UNSET function. It deletes one or more enviromental
 * variables. We are deleting from both maps in case the varible exists. 
 * 
 * @param data 
 */
void	ft_unset(t_data *data)
{
	int	i;

	i = 1;
	while (data->argv[i])
	{
		if (ft_key_exist(data->env, data->argv[i]))
		{
			free(ft_get_keymap(data->env, data->argv[i]));
			data->env->size--;
		}
		if (ft_key_exist(data->exp, data->argv[i]))
		{
			free(ft_get_keymap(data->exp, data->argv[i]));
			data->exp->size--;
		}
		i++;
	}
}
