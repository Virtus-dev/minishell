/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:35:25 by arigonza          #+#    #+#             */
/*   Updated: 2024/11/27 15:52:03 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Comprobar si hay que eliminar solo de env o tambien de la lista export

/**
 * @brief Replicates the UNSET function. It deletes one or more enviromental
 * variables. We are deleting from both maps in case the varible exists. 
 * 
 * @param data 
 */
void	ft_unset(t_data *data)
{
	t_map	*new_map;
	int	i;
	int	j;

	if (!data->argv[1])
		return ;
	i = 1;
	j = 0;
	new_map = malloc(sizeof(t_map));
	ft_map_init(new_map);
	while (data->argv[i])
	{
		while (data->env->keys[j])
		{
			if (ft_strcmp(data->env->keys[j]->key, data->argv[i]) != 0)
				ft_add_key(new_map, ft_new_key(data->env->keys[j]->key, data->env->keys[j]->value));
			j++;
		}
		i++;		
	}
	//ft_free_keys(data->env->keys);
	ft_free_map(data->env);
	data->env = new_map;
}
