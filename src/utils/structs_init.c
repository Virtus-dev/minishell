/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:09:20 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/23 16:02:37 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_init_data(int argc, char **env, t_token *tokens)
{
	t_data   *data;

	data = malloc(sizeof(t_data));
	data->argc = argc;
	data->fdin = STDIN_FILENO;
	data->fdout = STDOUT_FILENO;
	data->env = ft_fill_map(env);
	data->exp = ft_fill_map(env);
	data->tokens = tokens;
	
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

	i = 1;
	toklen = ft_toklen(data->tokens);
	token = get_next_token(data->tokens, toklen);
	data->argv[0] = token.cmd;
	while (token.cargs[i])
	{
		data->argv[i] = token.cargs[i];
		i++;
	}
	
}