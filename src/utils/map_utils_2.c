/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:47:48 by arigonza          #+#    #+#             */
/*   Updated: 2024/11/18 16:01:59 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_key_exist(t_map *map, char *key)
{
	int	i;

	i = 0;
	if (map && map->keys)
		return (0);
	while (map && map->keys[i])
	{
		if (ft_strcmp(key, map->keys[i]->key) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
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
	else
		ft_add_key(map, ft_new_key(key, value));
}

void	ft_print_map(t_data *data, t_map *map)
{
	size_t	i;

	if (!map)
		perror("No map to print\n");
	i = 0;
	while (map->keys[i])
	{
		ft_putstr_fd(map->keys[i]->key, data->fdout);
		ft_putstr_fd("=", data->fdout);
		ft_putstr_fd(map->keys[i]->value, data->fdout);
		ft_putchar_fd('\n', data->fdout);
		i++;
	}
}

/**
 * @brief Compares if a key exists on a map, if exists updates it's value,
 * if it's not, creates it.
 *
 * @param map The "key-value" data structure to check from.
 * @param values the env variables.
 */
void	ft_mapcmp_update(t_map *map, char *values)
{
	char	**splited;
	int		i;

	i = 0;
	splited = ft_mini_split(values, '=');
	while (splited[i])
	{
		if (ft_key_exist(map, splited[i]))
		{
			ft_update_map(map, splited[i + 1], splited[i]);
			i += 2;
		}
		else
			ft_add_key(map, ft_new_key(splited[i], splited[i + 1]));
		i++;
	}
}

void	ft_free_map(t_map *map)
{
	int	i;

	if (!map || !map->keys)
		perror("No map where free keys from");
	i = 0;
	while (map->keys[i])
	{
		free(map->keys[i]->key);
		free(map->keys[i]->value);
		free(map->keys[i]);
		i++;
	}
	free(map->keys);
	free(map);
}

void	ft_free_keys(t_key** keys)
{
	int	i;

	if (!keys)
	{
		perror("No keys to free\n");
		return;
	}
	i = 0;
	while (keys[i])
	{
		free(keys[i]->key);
		free(keys[i]->value);
		free(keys[i]);
		i++;
	}
	free(keys);
}