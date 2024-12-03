/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:14 by fracurul          #+#    #+#             */
/*   Updated: 2024/11/26 19:46:42 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *loop_check(char *input)
{
	char *input;


	if(!input)
	{
		printf("Exit\n");
		perror("NO input");
	}
	if(!check_input(input))
	{
		printf("Exit\n");
		perror("Bad input");
	}
	if(input[0] == '\n')
	{
		printf("\n");
	}
}