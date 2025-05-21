/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:08:58 by fracurul          #+#    #+#             */
/*   Updated: 2025/05/21 19:22:26 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_expander(t_data *data)
{
	char	*tmp;

	tmp = data->input;
	data->input = ft_expand(data, data->input);
	free(tmp);
}

static void	check_n_clean(t_data *data)
{
	ft_check_redir(data);
	free_tokens(data->tokens);
	data->tokens = NULL;
	ft_free_matrix(data->argv);
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	data->argv = NULL;
}

static void	ft_minishell_loop(t_data *data)
{
	if (data->input == NULL)
	{
		ft_exit(data);
		return ;
	}
	if (!check_input(data->input))
	{
		ft_putstr("Input is malformed\n");
		return (free(data->input));
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
	if (data->input)
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
