/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:10:38 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/08 23:33:24 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execpath(t_data* data)
{
	char	*path_aux;
	t_key	*path_key;
	char	**path_dirs;
	int		i;

	i = 0;
	path_key = ft_get_keymap(data->env, "PATH");
	path_aux = ft_strdup(path_key->value);
	path_dirs = ft_split(path_aux, ':');
	while (path_dirs[i])
	{
		path_aux = ft_strjoin(path_dirs[i], "/");
		free(path_dirs[i]);
		path_dirs[i] = ft_strjoin(path_aux, data->argv[0]);
		free(path_aux);
		if (access(path_dirs[i], F_OK) == 0 
			&& !ft_strnstr(data->argv[0], "./", 3))
		{
			free(data->argv[0]);
			data->argv[0] = ft_strdup(path_dirs[i]);
			break;
		}
		i++;
	}
	ft_free_matrix(path_dirs);
}

void	ft_runexec(t_data *data)
{
	char	**env;
	
	env = ft_revert_env(data->env);
	dup2(data->fdin, STDIN_FILENO);
	dup2(data->fdout, STDOUT_FILENO);
	if (execve(data->argv[0], data->argv, env) == -1)
	{
		ft_putstr_fd("bash: ", data->fdout);
		ft_putstr_fd(data->argv[0], data->fdout);
		ft_putstr_fd(": command not found\n", data->fdout);
		ft_free_matrix(env);
		exit(EXIT_FAILURE);
	}
}

char	**ft_revert_env(t_map *map)
{
	char	*tmp;
	char	**joined;
	int		i;

	i = 0;
	joined = (char**)ft_calloc(map->size + 1, sizeof(char*));
	if (!joined)
		return (NULL);
	while (map->keys[i])
	{
		tmp = ft_strjoin(map->keys[i]->key, "=");
		joined[i] = ft_strjoin(tmp, map->keys[i]->value);
		free(tmp);
		i++;
	}
	return (joined);
}
