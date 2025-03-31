/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:09:20 by arigonza          #+#    #+#             */
/*   Updated: 2025/03/31 16:46:48 by arigonza         ###   ########.fr       */
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
	data->lvl = 0;
	data->env = ft_fill_map(env);
	data->exp = ft_fill_map(env);
	data->tokens = NULL;
	
	return (data);
}

void	ft_map_init(t_map *map)
{
	map->size = 0;
	map->capacity = 2;
	map->keys = (t_key**)ft_calloc(sizeof(t_key *), map->capacity);
	if (!map->keys)
		perror(MALLOC_ERR);
}

t_token *get_next_token(t_token **token, int reset)
{
    static int position = 0;
	int	array_size;
	
	array_size = ft_toklen(token);
	printf("POSITION = %d\n", position);
	if (reset == TRUE)
		position = 0;
    if (position >= array_size)
    {
		position = 0;
        // Set up an "invalid token" with NULL fields to avoid uninitialized access
        t_token *invalid_token = malloc(sizeof(t_token));
        if (!invalid_token) 
			return NULL; // Check for malloc failure
        invalid_token->cmd = NULL;
        invalid_token->cargs = NULL;
        return invalid_token;
    }
    return (token[position++]);
}

void	ft_load_args(t_data *data, t_token *token)
{
	int	i;
	int	args_size;
	
	if (!data->tokens)
	{
		perror("No tokens found\n");
		return ;
	}
	if (token->cargs)
	{
		args_size = ft_matrix_size(token->cargs);
		data->argc = args_size + 1;
	}
	else
		args_size = 0;
    data->argv = ft_calloc(sizeof(char*), args_size + 2); // +1 for cmd and +1 for NULL terminator
    if (!data->argv) {
        perror("Memory allocation for argv failed\n");
        return;
    }
	i = 0;
	data->argv[i] = ft_strdup(token->cmd);
	while (token->cargs[i])
	{
		data->argv[i + 1] = ft_strdup(token->cargs[i]);
		i++;
	}
}
