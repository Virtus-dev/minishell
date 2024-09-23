/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:47:48 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/23 17:41:48 by arigonza         ###   ########.fr       */
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

void	ft_mapcmp_update(t_map *map, char *values)
{
	char	**splited;
	int		i;
	
	i = 0;
	splited = ft_split(values, '=');
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