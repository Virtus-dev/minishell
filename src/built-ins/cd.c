/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:26:51 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/23 00:16:09 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_data *data, char *owd)
{
	t_key	*home;

	owd = getcwd(NULL, 0);
	if (data->argc >= 2)
	{
		if (chdir(data->argv[1]) == 0)
			ft_update_dir(data, owd);
		else
			ft_putstr_fd("bash: cd: permission denied\n", data->fdout);
	}
	else
	{
		if (ft_key_exist(data->env, "HOME"))
		{
			home = ft_get_keymap(data->env, "HOME");
			if (chdir(home->value) == 0)
				ft_update_dir(data, owd);
			else
				ft_putstr_fd("bash: cd: HOME not reachable\n", data->fdout);
		}
		else
			ft_putstr_fd("bash: cd: HOME not set\n", data->fdout);
	}
	free(owd);
}

void	ft_oldpwd(t_data *data, char *owd)
{
	if (!data || !owd)
		return ;
	if (ft_key_exist(data->env, "OLDPWD"))
		ft_update_map(data->env, owd, "OLDPWD");
	else
		ft_add_key(data->env, ft_new_key("OLDPWD", owd));
}

void	ft_update_dir(t_data *data, char *owd)
{
	char	*nwd;

	nwd = getcwd(NULL, 0);
	if (!nwd)
	{
		data->status = ENOENT;
		return ;
	}
	if (ft_key_exist(data->env, "PWD"))
		ft_update_map(data->env, nwd, "PWD");
	else
		ft_add_key(data->env, ft_new_key("PWD", nwd));
	ft_oldpwd(data, owd);
	free (nwd);
	data->status = EXIT_SUCCESS;
}
