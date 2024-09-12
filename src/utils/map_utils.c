/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:34:13 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/12 19:57:02 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_key	*ft_get_keymap(t_map *map, char *key)
{
    int	i;
	
	i = 0;
	while (i < map->size)
	{
		if (ft_strcmp(map->key[i]->key, key) == 0)
			return (map->key[i]);
		i++;
	}
	return (NULL);
}

t_value	*ft_get_valmap(t_map *map, char *value)
{
	int	i;
	
	i = 0;
	while (i < map->size)
	{
		if (ft_strcmp(map->value[i]->value, value) == 0)
			return (map->value[i]);
		i++;
	}
	return (NULL);
}

t_map	*ft_fill_map(char **env)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	
	return (map);
}