/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:09:20 by arigonza          #+#    #+#             */
/*   Updated: 2024/11/08 18:40:30 by arigonza         ###   ########.fr       */
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
	data->tokens = NULL;
	
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

t_token get_next_token(t_token *token, int array_size)
{
	static int position = 0;

    if (position >= array_size)
    {
        t_token invalid_token = {NULL, NULL};
        return invalid_token;
    }
	return (token[position++]);
}

void	ft_load_args(t_data *data)
{
	int	toklen;
	int	i;
	t_token	token;

	if (!data->tokens)
		perror("No tokens found");
	i = 0;
	if (!data->tokens[1].cmd)
		token = data->tokens[0];
	else
	{
		toklen = ft_toklen(data->tokens);
		token = get_next_token(data->tokens, toklen);
	}
	if (!token.cmd)
		perror("Empty token found");
	data->argv = ft_calloc(sizeof(char*), (ft_matrix_size(token.cargs) + 1));
	data->argv[0] = token.cmd;
	while (token.cargs[i])
	{
		data->argv[i + 1] = token.cargs[i];
		i++;
	}
}
