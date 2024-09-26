/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:35:25 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/26 17:47:25 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_data *data, char **keys)
{
	int	i;

	i = 0;
	while (keys[i])
	{
		if (ft_key_exist(data->env, keys[i]))
			free(ft_get_keymap(data->env, keys[i]));
		if (ft_key_exist(data->exp, keys[i]))
			free(ft_get_keymap(data->exp, keys[i]));
		i++;
	}
}