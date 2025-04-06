/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:42:44 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/05 20:44:02 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getvar(t_map *map, char *key)
{
	t_key	*var;
	if (!key || !map)
	{
		ft_putstr("NO KEY OR MAP PROVIDED\n");
		return (NULL);
	}
	var = ft_get_keymap(map, key);
	if (!var)
	{
		ft_putstr("Not value found for the given key\n");
		return (NULL);
	}
	else
		return (var->value);
}