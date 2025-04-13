/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/13 15:54:14 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


void    ft_minishell_init(t_data *data)
{
    while (1)
	{
		ft_signal();
		data->input = readline("Hi minishell\n");
		ft_set_signal();
		if (data->input == NULL)
		{
			ft_putstr_fd(BAD_INPUT, data->fdout);
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			if (check_quotes(data->input))
			{
				ft_putstr_fd("You must close quotes\n", data->fdout);
				data->status = 1;
			}
			if (!ft_is_all_space(data->input, data))
				ft_check_redir(data);
			//printf("%s\n", data->argv[i]);
		}
		free(data->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	(void)argv;
	
	using_history();
	data = ft_init_data(argc, env);
	ft_minishell_init(data);
	ft_free_resources(data);
	free(data);
	return (0);
}
/*
void	free_token_result(t_token **cmds)
{
	int i = 0;
	int j;

	if (!cmds)
		return;
	while (cmds[i])
	{
		j = 0;
		if (cmds[i]->cmd)
			free(cmds[i]->cmd);
		if (cmds[i]->cargs)
		{
			while (cmds[i]->cargs[j])
				free(cmds[i]->cargs[j++]);
			free(cmds[i]->cargs);
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

//Imprime estructura final agrupada
void	print_cmd_structure(t_token **cmds)
{
	int i, j;

	i = 0;
	while (cmds[i])
	{
		printf("  ➤ Comando[%d]: %s\n", i, cmds[i]->cmd ? cmds[i]->cmd : "(null)");
		j = 0;
		while (cmds[i]->cargs && cmds[i]->cargs[j])
		{
			printf("     Arg[%d]: \"%s\"\n", j, cmds[i]->cargs[j]);
			j++;
		}
		i++;
	}
}

//test de tokenización completo
void	run_tokenizer_test(const char *input)
{
	char		**tokens;
	t_token		**cmds;

	printf("🟡 Input: %s\n\n", input);

	tokens = tokenizer(input);

	printf("Tokens generados por tokenizer():\n");
	for (int i = 0; tokens[i]; i++)
		printf("  [%d]: \"%s\"\n", i, tokens[i]);
	printf("\n");

	cmds = tokenize_command(tokens);
	print_cmd_structure(cmds);

	printf("✅ Comandos correctamente agrupados (bash-like)\n");
	printf("--------------------------------------------------\n");

	ft_free_matrix(tokens);
	free_token_result(cmds);
}

int	main(void)
{
	//Esto reemplaza el bucle infinito ejecutas con Valgrind
	run_tokenizer_test("echo \"hola mundo\" | wc -l");
	run_tokenizer_test("cat << EOF | grep error > salida.txt");
	run_tokenizer_test("ls -la | grep main.c | wc -l");
	run_tokenizer_test("echo 'esto > no es redir'");
	run_tokenizer_test("cat < entrada.txt >> salida.txt");
	run_tokenizer_test("echo '' | grep hola > file.txt");
	run_tokenizer_test("grep \"|\" archivo.txt");
	run_tokenizer_test("ls | cat -e | tr -d '\n'");

	return (0);
}*/