/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:09:20 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/20 10:29:36 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_init_data(int argc, char **env)
{
	t_data   *data;

	data = malloc(sizeof(t_data));
	data->argc = argc;
	data->fdin = STDIN_FILENO;
	data->fdout = STDOUT_FILENO;
	data->env = ft_fill_map(env);
	data->exp = ft_fill_map(env);
	data->token = malloc(sizeof(t_token*));
	
	return (data);
}

void	ft_map_init(t_map *map)
{
	map->size = 0;
	map->capacity = 10;
	map->keys = malloc(sizeof(t_key *) * map->capacity);
	if (!map->keys)
		perror(MALLOC_ERR);
}

void	ft_load_token(t_data *data, char **tokens)
{
	int	i;
	int	j;
	char	**aux;

	i = 0;
	j = 0;
	aux = NULL;
	while (tokens[i])
	{	
		if (ft_builtin_check(tokens[i]))
		{
			aux[j++] = tokens[i++];
			while (!ft_builtin_check(tokens[i]))
				aux[j++] = tokens[i++];
			
			ft_tokadd_back(data->token, ft_new_token(ft_dbstrdup(aux)));
		}
		i++;
	}
}
