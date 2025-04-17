/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:42:44 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 16:10:48 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getvar(t_map *map, char *key)
{
	t_key	*var;

	if (!key || !map)
	{
		ft_putstr("NO KEY OR MAP PROVIDED\n");
		return (NULL);
	}
	var = ft_get_keymap(map, key);
	if (!var)
	{
		ft_putstr("Not value found for the given key\n");
		return (NULL);
	}
	else
		return (var->value);
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

void	ft_free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->keys)
		ft_free_keys(map->keys);
	free(map);
}
