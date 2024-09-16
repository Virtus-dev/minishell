/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:09:20 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/17 00:38:42 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*ft_init_data(int argc, char **argv, char **env)
{
	t_data   *data;

	data = malloc(sizeof(t_data));
	data->argc = argc;
	data->argv = ft_dbstrdup(env);
	data->fdin = STDIN_FILENO;
	data->fdout = STDOUT_FILENO;
	data->env = ft_fill_map(env);
}

void	ft_map_init(t_map *map)
{
	map->size = 0;
	map->capacity = 10;
	map->keys = malloc(sizeof(t_key *) * map->capacity);
	if (!map->keys)
		perror(MALLOC_ERR);
}
