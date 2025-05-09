/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:10:38 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/09 12:07:53 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_full_path(char *dir, char *cmd)
{
	char	*pre;
	char	*full_path;

	pre = ft_strjoin(dir, "/");
	full_path = ft_strjoin(pre, cmd);
	free(pre);
	return (full_path);
}

static int	ft_path_replace(t_data *data, char **argv, char **paths)
{
	int		i;
	char	*replacement;

	i = 0;
	while (paths[i])
	{
		replacement = ft_full_path(paths[i], argv[0]);
		if (access(replacement, F_OK) == 0
			&& !ft_strnstr(data->argv[0], "./", 3))
		{
			free(argv[0]);
			argv[0] = ft_strdup(replacement);
			free(replacement);
			return (1);
		}
		free(replacement);
		i++;
	}
	return (0);
}

void	ft_execpath(t_data *data)
{
	t_key	*path_key;
	char	**path_dirs;
	char	*path_aux;

	path_key = ft_get_keymap(data->env, "PATH");
	if (!path_key || !path_key->value)
		return ;
	path_aux = ft_strdup(path_key->value);
	path_dirs = ft_split(path_aux, ':');
	free(path_aux);
	ft_path_replace(data, data->argv, path_dirs);
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
	joined = (char **)ft_calloc(map->size + 1, sizeof(char *));
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
