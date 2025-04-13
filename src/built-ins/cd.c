/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:26:51 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/13 12:47:03 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_cd(t_data *data, char *owd)
{
	t_key	*home;

	owd = getcwd(NULL, 0);
	if (!chdir(data->argv[1]) && data->argc >= 2)
		ft_update_dir(data, owd);
	else if (data->argc == 1)
	{
		if (ft_key_exist(data->env, "HOME"))
		{
			home = ft_get_keymap(data->env, "HOME");
			printf("cd: trying to chdir to [%s]\n", home->value);
			chdir(home->value);
			ft_update_dir(data, owd);
		}
		else
			ft_putstr_fd("bash: cd: HOME not setted yet\n", data->fdout);
	}
	else if (chdir(data->argv[1]))
		ft_putstr_fd("bash: cd: permission denied\n", data->fdout);
	free (owd);
}*/

void	ft_cd(t_data *data, char *owd)
{
	t_key	*home;

	owd = getcwd(NULL, 0);
	if (data->argc >= 2)
	{
		if(chdir(data->argv[1]) == 0)
			ft_update_dir(data, owd);
		else
			ft_putstr_fd("bash: cd: permission denied\n", data->fdout);
	}
	else
	{
		if (ft_key_exist(data->env, "HOME"))
		{
			home = ft_get_keymap(data->env, "HOME");
			printf("cd: trying to chdir to [%s]\n", home->value);
			if(chdir(home->value) == 0)
				ft_update_dir(data, owd);
			else
				ft_putstr_fd("bash: cd: HOME not reachable\n", data->fdout);
		}
		else
			ft_putstr_fd("bash: cd: HOME not set\n", data->fdout);
	}
	free(owd);
}


/*void	ft_oldpwd(t_data *data, char *owd, char *nwd)
{
	t_key	*nkey;

	if (ft_strcmp(owd, nwd) != 0)
	{
		if (ft_key_exist(data->env, "OLDPWD"))
			ft_update_map(data->env, owd, "OLDPWD");
		else
		{
			nkey = ft_new_key("OLDPWD", owd);
			ft_add_key(data->env, nkey);
		}
	}
}*/

void	ft_oldpwd(t_data *data, char *owd)
{
	if (!data || !owd)
		return ;
	if(ft_key_exist(data->env, "OLDPWD"))
		ft_update_map(data->env, owd, "OLDPWD");
	else
		ft_add_key(data->env, ft_new_key("OLDPWD", owd));
}

/*void	ft_update_dir(t_data *data, char *owd)
{
	char	*nwd;

	nwd = getcwd(NULL, 0);
	if (ft_key_exist(data->env, "PWD"))
		ft_update_map(data->env, nwd, "PWD");
	ft_oldpwd(data, owd, nwd);
	free(nwd);
}*/

void	ft_update_dir(t_data *data, char *owd)
{
	char	*nwd;

	nwd = getcwd(NULL, 0);
	if (!nwd)
		return ;
	if(ft_key_exist(data->env, "PWD"))
		ft_update_map(data->env, nwd, "PWD");
	else
		ft_add_key(data->env, ft_new_key("PWD", nwd));
	ft_oldpwd(data, owd);
	free (nwd);
}
