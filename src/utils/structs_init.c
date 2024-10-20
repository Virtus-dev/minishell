/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:09:20 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/20 18:35:45 by arigonza         ###   ########.fr       */
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

/*
	TODO
	Quizas valga mas la pena por sencillez aprovechar que strtok devuelve los tokens
	por llamadas para cargar en argv dicha llamada individual, y asi no tener
	que preocuparnos de las posiciones de los tokens. 	
 */
void	ft_load_tokens(t_data *data, char *input)
{
	int	i;
	t_token	*token;

	token = tokenize_command(input, 0);
	while (token)
	{
		data->tokens[i] = token;
		token = tokenize_command(input, 0);
	}
}
