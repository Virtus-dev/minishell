/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:50:15 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/05 18:53:33 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_expandable(char *var)
{
	if (ft_strchr(var, '$'))
		return (TRUE);
	else
		return (FALSE);
}