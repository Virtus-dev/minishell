/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:35:25 by arigonza          #+#    #+#             */
/*   Updated: 2024/11/24 11:35:14 by arigonza         ###   ########.fr       */
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
	t_key	*key;

	i = 1;
	while (data->argv[i])
	{
		if (ft_key_exist(data->env, data->argv[i]))
		{
			key = ft_get_keymap(data->env, data->argv[i]);
			free(key->value);
			free(key->key);
			free(key);
			data->env->size--;
		}
		if (ft_key_exist(data->exp, data->argv[i]))
		{	
			key = ft_get_keymap(data->exp, data->argv[i]);
			free(key->value);
			free(key->key);
			free(key);
			data->exp->size--;
		}
		i++;
	}
}
