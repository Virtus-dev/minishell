/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:10:38 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/25 20:20:18 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*full_path;
	t_key	*path_var;
	char	**path_dirs;
	int		i;

	i = 0;
	path_var = ft_get_keymap(data->env, "PATH");
	if (!path_var)
		return;
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return;
	while (path_dirs[i])
	{
		path_aux = ft_strjoin(path_dirs[i], "/");
		full_path = ft_strjoin(path_aux, data->argv[0]);
		free(path_aux);
		if (acces(full_path, F_OK | X_OK) == 0 
			&& !ft_strnstr(data->argv[0], "./", 3))
		{
			free(data->argv[0]);
			data->argv[0] = ft_strdup(full_path);
			free(full_path);break;
		}
		free(full_path);
		i++;
	}
	ft_free_matrix(path_dirs);
}

void	ft_runexec(t_data *data)
{
	
}