/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:17:03 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/12 23:41:19 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


//void    ft_minishell_init(t_data *data)
//{
//    while (1)
//	{
//		ft_signal();
//		data->input = readline("Hi minishell\n");
//		ft_set_signal();
//		if (data->input == NULL)
//		{
//			ft_putstr_fd(BAD_INPUT, data->fdout);
//			break ;
//		}
//		if (data->input[0] != '\0')
//		{
//			add_history(data->input);
			/*if (check_quotes(data->input))
			{
				ft_putstr_fd("You must close quotes\n", data->fdout);
				data->status = 1;
			}
			*/
//			if (!ft_is_all_space(data->input, data))
//				ft_check_redir(data);
			//printf("%s\n", data->argv[i]);
//		}
//		free(data->input);
//	}
//}

/*int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	(void)argv;
	
	using_history();
	data = ft_init_data(argc, env);
	ft_minishell_init(data);
	ft_free_resources(data);
	free(data);
	return (0);
}*/

void	free_token_result(t_token **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds && cmds[i])
	{
		free(cmds[i]->cmd);
		j = 0;
		while (cmds[i]->cargs && cmds[i]->cargs[j])
			free(cmds[i]->cargs[j++]);
		free(cmds[i]->cargs);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void print_raw_tokens(char **tokens)
{
	int i = 0;

	printf("Tokens generados por tokenizer():\n");
	while (tokens[i])
	{
		printf("  [%d]: \"%s\"\n", i, tokens[i]);
		i++;
	}
	printf("\n");
}

int compare_token_result(t_token **result, const char **expected_cmds, const char ***expected_args)
{
	int i = 0, j;

	while (result[i] && expected_cmds[i])
	{
		if (strcmp(result[i]->cmd, expected_cmds[i]) != 0)
			return (0);
		j = 0;
		while (result[i]->cargs[j] && expected_args[i][j])
		{
			if (strcmp(result[i]->cargs[j], expected_args[i][j]) != 0)
				return (0);
			j++;
		}
		if (result[i]->cargs[j] || expected_args[i][j])
			return (0);
		i++;
	}
	if (result[i] || expected_cmds[i])
		return (0);
	return (1);
}

void	print_token_structure(t_token **cmds)
{
	int i = 0;
	int j;

	while (cmds[i])
	{
		printf("  ➤ Comando[%d]: %s\n", i, cmds[i]->cmd);
		j = 0;
		while (cmds[i]->cargs && cmds[i]->cargs[j])
		{
			printf("     Arg[%d]: \"%s\"\n", j, cmds[i]->cargs[j]);
			j++;
		}
		i++;
	}
}
void run_cmd_test(const char *input, const char **expected_cmds, const char ***expected_args)
{
	char **tokens = tokenizer(input);
	t_token **cmds = tokenize_command(tokens);

	printf("🟡 Input: %s\n\n", input);

	print_raw_tokens(tokens);           // Tokens planos desde tokenizer
	print_token_structure(cmds);        // Estructura t_token

	if (compare_token_result(cmds, expected_cmds, expected_args))
		printf("\n✅ Comandos correctamente agrupados (bash-like)\n");
	else
		printf("\n❌ Error en tokenización por comandos\n");

	printf("--------------------------------------------------\n");

	free_token_result(cmds);
	// Free tokens también (si están duplicados)
	for (int i = 0; tokens[i]; i++)
		free(tokens[i]);
	free(tokens);
}

int	main(void)

{
	// Test 1: echo "hola mundo" | wc -l
	const char *cmds1[] = {"echo", "wc", NULL};
	const char *args1[] = {"hola mundo", NULL};
	const char *args2[] = {"-l", NULL};
	const char **arg_sets1[] = {args1, args2, NULL};

	run_cmd_test("echo \"hola mundo\" | wc -l", cmds1, arg_sets1);

	// Test 2: ls | grep main
	const char *cmds2[] = {"ls", "grep", NULL};
	const char *args3[] = {NULL};
	const char *args4[] = {"main", NULL};
	const char **arg_sets2[] = {args3, args4, NULL};

	run_cmd_test("ls | grep main", cmds2, arg_sets2);

	// Test 3: múltiple pipes y args
	const char *cmds3[] = {"ls", "grep", "wc", NULL};
	const char *args5[] = {"-la", NULL};
	const char *args6[] = {"main.c", NULL};
	const char *args7[] = {"-l", NULL};
	const char **arg_sets3[] = {args5, args6, args7, NULL};

	run_cmd_test("ls -la | grep main.c | wc -l", cmds3, arg_sets3);

	// Test 4: redirección dentro de comillas
	const char *cmds4[] = {"echo", NULL};
	const char *args8[] = {"esto > no es redir", NULL};
	const char **arg_sets4[] = {args8, NULL};

	run_cmd_test("echo \"esto > no es redir\"", cmds4, arg_sets4);

	// Test 5: redirecciones múltiples
	const char *cmds5[] = {"cat", NULL};
	const char *args9[] = {"<", "entrada.txt", ">>", "salida.txt", NULL};
	const char **arg_sets5[] = {args9, NULL};

	run_cmd_test("cat < entrada.txt >> salida.txt", cmds5, arg_sets5);

	// Test 6: heredoc simple
	const char *cmds6[] = {"cat", NULL};
	const char *args10[] = {"<<", "EOF", NULL};
	const char **arg_sets6[] = {args10, NULL};

	run_cmd_test("cat << EOF", cmds6, arg_sets6);

	// Test 7: argumento vacío entre comillas
	const char *cmds7[] = {"echo", NULL};
	const char *args11[] = {"", NULL};
	const char **arg_sets7[] = {args11, NULL};

	run_cmd_test("echo \"\"", cmds7, arg_sets7);

	return 0;
}
