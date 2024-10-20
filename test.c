/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/20 13:26:48 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argv;
	t_data	*data;
	char 	*input;
	char	**str;
	data = ft_init_data(argc, env);

	while(1)
	{
		// guardar lectura del usuario en una var.
		input = readline("Minishell$ ");
		data->argv = tokenize_command(input, 0);
		//si no hay contenido nos salimos (ctrl + D)
		if(!input)
		{
			printf("Exit \n");
			break;
		}
		//prueba.
		printf("Entrada: %s\n", input);
		//si tenemos entrada, la añadimos al historial.
		if(input)
			add_history(input);
		
		if(!check_input(input))
		{
			printf("syntax error\n");
			continue;
		}
		ft_exec(data);
		//liberar lo que hemos leido, para realizar una nueva lectura.
		free(input);
	}
}
