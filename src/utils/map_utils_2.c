/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:47:48 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/19 13:10:18 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_key_exist(t_map *map, char *key)
{
	int	i;

	i = 0;
	while (map && map->keys[i])
	{
		if (ft_strcmp(key, map->keys[i]->key) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_update_map(t_map *map, char *value, char *key)
{
	t_key	*nkey;
	
	if (ft_key_exist(map, key))
	{
		nkey = ft_get_keymap(map, key);
		free(nkey->value);
		nkey->value = ft_strdup(value);
	}
}

void	ft_print_map(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->env->size > i)
	{
		ft_putstr_fd(data->env->keys[i]->key, data->fdout);
		ft_putstr_fd("=", data->fdout);
		ft_putstr_fd(data->env->keys[i]->value, data->fdout);
		ft_putchar_fd('\n', data->fdout);
		i++;
	}
}