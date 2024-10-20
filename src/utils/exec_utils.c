/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:10:38 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/20 09:31:44 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the parameter passed by is or is not a built-in.
 * 
 * @param data Struct with all the main information. 
 * @param str The supossed built-in we are going to check.
 * @return int Executes and Returns the kind of built-in.
 */
int	ft_builtin_check(char *str)
{
	if (!ft_strcmp(str, "echo") || ft_strcmp(str, "ECHO"))
		return (ECHO);
	if (!ft_strcmp(str, "cd") || ft_strcmp(str, "CD"))
		return (CD);
	if (!ft_strcmp(str, "export") || ft_strcmp(str, "EXPORT"))
		return (EXP);
	if (!ft_strcmp(str, "unset") || ft_strcmp(str, "UNSET"))
		return (UNST);
	if (!ft_strcmp(str, "env") || ft_strcmp(str, "ENV"))
		return (ENV);
	if (!ft_strcmp(str, "exit") || ft_strcmp(str, "EXIT"))
		return (EXIT);
	if (!ft_strcmp(str, "./minishell"))
		return (DEF);
	return (FALSE);
}

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
		ft_putstr_fd("bash: ", data->fdin);
		ft_putstr_fd(data->argv[0], data->fdin);
		ft_putstr_fd(": command not found\n", data->fdout);
		ft_free_matrix(env);
	}
}

char	**ft_revert_env(t_map *map)
{
	char	*tmp;
	char	*tmp2;
	char	**joined;
	int		i;

	i = 0;
	joined = (char**)ft_calloc(map->size, sizeof(char*));
	if (!joined)
		return (NULL);
	while (map->keys[i])
	{
		tmp = ft_strjoin(map->keys[i]->key, "=");
		tmp2 = ft_strjoin(tmp, map->keys[i]->value);
		joined[i] = ft_strdup(tmp2);
		free(tmp);
		free(tmp2);
		i++;
	}
	return (joined);
}