/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:14 by fracurul          #+#    #+#             */
/*   Updated: 2024/12/03 16:07:43 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *loop_check(char *input)
{
	char *input;
	int len;

	len = ft_strlen(input);
	if(len == 0)
		free(input);
	if(!check_input(input))
	{
		free(input);
	}
	
}