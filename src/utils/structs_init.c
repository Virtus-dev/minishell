/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:09:20 by arigonza          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/10 15:03:37 by arigonza         ###   ########.fr       */
=======
/*   Updated: 2024/11/08 18:56:00 by arigonza         ###   ########.fr       */
>>>>>>> 6242efde711e56e223f731e4172ef29d119474bf
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
	
	return (data);
}

void	ft_map_init(t_map *map)
{
	map->size = 0;
	map->capacity = 1000;
	map->keys = malloc(sizeof(t_key *) * map->capacity);
	if (!map->keys)
		perror(MALLOC_ERR);
}

t_token *get_next_token(t_token **token, int array_size)
{
    static int position = 0;

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

void	ft_load_args(t_data *data)
{
	int	toklen;
	int	i;
	t_token	*token;
	
	if (!data->tokens)
		perror("No tokens found");
	i = 0;
	if (!data->tokens[0] || !data->tokens[1])
		token = data->tokens[0];
	else
	{
		toklen = ft_toklen(data->tokens);
		token = get_next_token(data->tokens, toklen);
	}
<<<<<<< HEAD
	if (!token || !token->cmd) 
=======
	data->argv = ft_calloc(sizeof(char*), (ft_matrix_size(token.cargs) + 1));
	data->argv[0] = token.cmd;
	while (token.cargs[i])
>>>>>>> 6242efde711e56e223f731e4172ef29d119474bf
	{
        perror("Empty token found or invalid command");
        return; // Early exit if token is invalid
    }
	
	int args_size = ft_matrix_size(token->cargs);
    data->argv = ft_calloc(sizeof(char*), args_size + 2); // +1 for cmd and +1 for NULL terminator
    if (!data->argv) {
        perror("Memory allocation for argv failed");
        return;
    }
	data->argv[0] = token->cmd;
	while (token->cargs[i])
	{
		data->argv[i + 1] = token->cargs[i];
		i++;
	}
}
