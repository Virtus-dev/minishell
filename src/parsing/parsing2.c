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

int check_line2(char *line)
{
	char *input;

	if(input[0] != '\n' && input[0] != '\0')
		{
			input = ft_strtrim(input, "\n\t\f\r\v ")
			if(!input)
				return(NULL);
			if(!check_input(input))
				return(NULL);
		}
	return; //no se que deberia poner aqui
}

void loop_check(void)
{
	char *input;

	while(1)
	{
		input = readline("Minishell: ")
		if(input == NULL)
		{
			printf("Exit\n");
			perror("NO input");
		}
		if(!check_line2(input))
		{
			printf("Exit\n")
			perror("Bad input");
		}
		if(input == '\0')
		{
			printf('\n');
			continue;
		}
		add_history(input);
	}
}