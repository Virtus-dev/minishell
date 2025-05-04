/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:34:13 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/03 21:56:15 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_key	*ft_new_key(char *name, const char *value)
{
	t_key	*new_key;

	if (!name)
		return (NULL);
	new_key = ft_calloc(1, sizeof(t_key));
	if (!new_key)
		return (NULL);
	new_key->key = ft_strdup(name);
	new_key->value = ft_strdup(value);
	if (!new_key->key)
	{
		free(new_key->key);
		free(new_key);
	}
	return (new_key);
}

static int	expand_key(t_map *map)
{
	t_key	**new_keys;
	size_t	i;

	new_keys = ft_calloc(map->capacity * 2, sizeof(t_key *));
	if (!new_keys)
	{
		perror("Realloc error");
		return (0);
	}
	i = 0;
	while (i < map->size)
	{
		new_keys[i] = map->keys[i];
		i++;
	}
	free(map->keys);
	map->keys = new_keys;
	map->capacity *= 2;
	return (1);
}

void	ft_add_key(t_map *map, t_key *key)
{
	if (!map || !key)
	{
		perror("Map or key not found");
		return ;
	}
	if (map->size == map->capacity && !expand_key(map))
		return ;
	map->keys[map->size] = key;
	map->size++;
}

t_key	*ft_get_keymap(t_map *map, char *key)
{
	size_t	i;

	i = 0;
	while (i < map->size)
	{
		if (ft_strcmp(map->keys[i]->key, key) == 0)
			return (map->keys[i]);
		i++;
	}
	return (NULL);
}
