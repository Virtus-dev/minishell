/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:08:58 by fracurul          #+#    #+#             */
/*   Updated: 2025/05/20 18:27:42 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_minishell_init(t_data *data)
{
	char	*expand;

	while (1)
	{
		ft_setup_parent_signals();
		data->input = readline("$minishell>");
		if (data->input == NULL)
		{
			ft_exit(data);
			//escribir exit\n
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			if (!ft_is_all_space(data->input, data))
			{
				if (ft_is_expandable(data->input))
				{
					expand = ft_expand(data->input, data->env);
					ft_putstr_fd(expand, data->fdout);
					free(expand);
				}
				ft_check_redir(data);
				free_tokens(data->tokens);
				data->tokens = NULL;
				ft_free_matrix(data->argv);
				data->argv = NULL;
			}
		}
		free(data->input);
	}
}*/

static void	ft_expander(t_data *data)
{
	char	*expand;

	expand = ft_expand(data, data->input);
	ft_putstr_fd(expand, data->fdout);
	free(expand);
}

static void	check_n_clean(t_data *data)
{
	ft_check_redir(data);
	free_tokens(data->tokens);
	data->tokens = NULL;
	ft_free_matrix(data->argv);
	data->argv = NULL;
}

static void	ft_minishell_loop(t_data *data)
{
	if (data->input == NULL)
	{
		ft_exit(data);
		ft_putstr("Exit\n");
		return ;
	}
	if (data->input[0] != '\0')
	{
		add_history(data->input);
		if (!ft_is_all_space(data->input, data))
		{
			if (ft_is_expandable(data->input))
				ft_expander(data);
			check_n_clean(data);
		}
	}
	free(data->input);
}

void	ft_minishell_init(t_data *data)
{
	while (1)
	{
		ft_setup_parent_signals();
		data->input = readline("minishell>");
		ft_minishell_loop(data);
	}
}

char	*ft_getenv(t_map *env, char *key)
{
	t_key	*found;

	found = ft_get_keymap(env, key);
	if (!found || !found->value)
		return (NULL);
	return (ft_strdup(found->value));
}
