/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:34:13 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/13 13:10:53 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*t_key	*ft_new_key(char *name, char *value)
{
	t_key	*new_key;

	new_key = malloc(sizeof(t_key));
	if (!new_key)
		return(NULL);
	new_key->key = ft_strdup(name);
	new_key->value = ft_strdup(value);
	if (!new_key->key)
	{
		free(new_key->key);
		free(new_key->value);
		free(new_key);
		return (NULL);
	}
	return (new_key);
}*/
t_key	*ft_new_key(char *name, const char *value)
{
	t_key	*new_key;

	if (!name || !value)
		return (NULL);
	new_key = ft_calloc(1, sizeof(t_key));
	if(!new_key)
		return (NULL);
	new_key->key = ft_strdup(name);
	new_key->value = ft_strdup(value);
	if(!new_key->key)
	{
		free(new_key->key);
		//free(new_key->value);
		free(new_key);
	}
	return (new_key);
}

/*void	ft_add_key(t_map *map, t_key *key)
{
	size_t	i;

	if (!map || !key)
	{
		perror("No map or key found");
		return ;
	}
	i = 0;
	if (map->size == map->capacity)
	{
		map->capacity *= 2;
		t_key	**new_keys;
		new_keys = (t_key**)ft_calloc(sizeof(t_key *), map->capacity);
		if (!new_keys)
		{
			perror("Realloc error\n");
			return ;
		}
		while (i < map->size)
		{
			new_keys[i] = map->keys[i];
			i++;
		}
		//ft_free_keys(map->keys);
		free(map->keys);
		map->keys = new_keys;
	}
	map->keys[map->size] = key;
	map->size++;
}*/

static int	expand_key(t_map *map)
{
	t_key	**new_keys;
	size_t	i;

	new_keys= ft_calloc(map->capacity * 2, sizeof(t_key *));
	if(!new_keys)
	{
		perror("Realloc error");
		return (0);
	}
	i = 0;
	while(i < map->size)
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
	map->keys[map->size] = NULL;
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

t_key	*ft_get_valmap(t_map *map, char *value)
{
	size_t	i;

	i = 0;
	while (i < map->size)
	{
		if (ft_strcmp(map->keys[i]->value, value) == 0)
			return (map->keys[i]);
		i++;
	}
	return (NULL);
}

t_map	*ft_fill_map(char **env)
{
	t_map	*map;
	char	**splited;
	int		i;
	int		j;

	i = 0;
	map = malloc(sizeof(t_map));
	if (!map)
		return (perror(MALLOC_ERR), NULL);
	ft_map_init(map);
	while (env[i])
	{
		j = 0;
		splited = ft_mini_split(env[i], '=');
		while (splited[j] && splited[j + 1])
		{
			ft_add_key(map, ft_new_key(splited[j], splited[j + 1]));
			j++;
		}
		ft_free_matrix(splited);
		i++;
	}
	return (map);
}
