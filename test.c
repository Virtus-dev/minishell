/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/20 12:25:52 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int main(int argc, char **argv, char **env)
{
	t_data	*data;

	data = ft_init_data(argc, argv, env);
	while (1)
	{
		data->input = readline("Waiting for instructions...\n");
		if (data->input == NULL)
		{
			ft_putstr_fd("QUITTING MINISHELL\n", data->fdout);
			break;
		}
		if (!ft_strcmp(data->input, "pwd"))
			ft_pwd(data);
		if (!ft_strcmp(data->input, "cd"))
			ft_cd(data, data->input);
		if (!ft_strcmp(data->input, "echo"))
			ft_echo(data);
		if (!ft_strcmp(data->input, "env"))
			ft_env(data);
		if (!ft_strcmp(data->input, "exp"))
			ft_export(data);
		if(data->input)
			add_history(data->input);
		if(!(check_line(data->input)))
		{
			ft_putstr_fd(PARS_ERR, data->fdout);
			continue;
		}
	}
	free(data->input);
	clear_history();
	return (FALSE);
}*/

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
		str = tokenize_command(input, 0);
		if (ft_builtin_check(str[0]))
		{
			if (ft_strcmp(str[0], ".."))
			{
				t_key *key = ft_get_keymap(data->env, "OLDPWD");
				chdir(key->value);
			}
		}
		//liberar lo que hemos leido, para realizar una nueva lectura.
		free(input);
	}
}
