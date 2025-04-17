/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:35:25 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 15:47:00 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_map	*filter_map(t_map *map, char **args)
{
	t_map	*new;
	int		i;
	int		j;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	ft_map_init(new);
	i = 0;
	while (map->keys[i])
	{
		j = 1;
		while (args[j] && ft_strcmp(args[j], map->keys[i]->key))
			j++;
		if (!args[j])
			ft_add_key(new, ft_new_key(map->keys[i]->key, map->keys[i]->value));
		i++;
	}
	return (new);
}

/**
 * @brief Replicates the UNSET function. It deletes one or more enviromental
 * variables. We are deleting from both maps in case the varible exists.
 *
 * @param data
 */
void	ft_unset(t_data *data)
{
	t_map	*new_env;
	t_map	*new_exp;

	new_env = filter_map(data->env, data->argv);
	new_exp = filter_map(data->exp, data->argv);
	ft_free_map(data->env);
	ft_free_map(data->exp);
	data->env = new_env;
	data->exp = new_exp;
}
