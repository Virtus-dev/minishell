/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/20 17:43:45 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int main(int argc, char **argv, char **env)
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

int main() {
    char str[100] = "ls -l | grep test";
    int num_commands = 0;
    t_token *commands = tokenize_command(str, &num_commands);

    // Imprimir los resultados
    for (int i = 0; i < num_commands; i++) {
        printf("Command: %s\n", commands[i].cmd);
        printf("Arguments: ");
        for (int j = 0; commands[i].cargs[j] != NULL; j++) {
            printf("%s ", commands[i].cargs[j]);
        }
        printf("\n");
    }

    // Liberar la memoria
    free_tokens(commands, num_commands);

    return 0;
}
*/

void free_tokens(t_token *tokens, int num_commands) {
    for (int i = 0; i < num_commands; i++) {
        free(tokens[i].cmd);
        for (int j = 0; tokens[i].cargs[j] != NULL; j++) {
            free(tokens[i].cargs[j]);
        }
        free(tokens[i].cargs);
    }
    free(tokens);
}


int main() {
    char str[100] = "echo -n 'hola' >> test.txt";
    int num_commands = 0;
    t_token *commands = tokenize_command(str, &num_commands);

    // Imprimimos los resultados
    for (int i = 0; i < num_commands; i++) {
        printf("Command: %s\n", commands[i].cmd);
        printf("Arguments: ");
        for (int j = 0; commands[i].cargs[j] != NULL; j++) {
            printf("%s ", commands[i].cargs[j]);
        }
        printf("\n");
    }

    // Liberamos la memoria
    free_tokens(commands, num_commands);

    return 0;
}