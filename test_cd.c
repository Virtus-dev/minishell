/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:44:30 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/13 11:45:26 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test for tokens
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

//test cd
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

//  Imprime el entorno actual para debugging
void	debug_print_keys(t_map *map)
{
	size_t	i;

	if (!map || !map->keys)
	{
		printf("🔍 [DEBUG] Mapa vacío o sin claves.\n");
		return;
	}

	printf("\n🧠 [DEBUG] Claves actuales en el entorno:\n");
	i = 0;
	while (map->keys[i])
	{
		printf("  - [%zu] %s = %s\n",
			i,
			map->keys[i]->key ? map->keys[i]->key : "NULL",
			map->keys[i]->value ? map->keys[i]->value : "NULL");
		i++;
	}
}

// Guarda historial de cambios (PWD y OLDPWD)
void	log_env_change(t_map *env)
{
	t_key *pwd = ft_get_keymap(env, "PWD");
	t_key *oldpwd = ft_get_keymap(env, "OLDPWD");
	char	*entry;
	char	*tmp;

	if (pwd && pwd->value)
	{
		tmp = ft_strjoin("PWD = ", pwd->value);
		entry = ft_strjoin("[HIST] ", tmp);
		add_history(entry);
		free(tmp);
		free(entry);
	}

	if (oldpwd && oldpwd->value)
	{
		tmp = ft_strjoin("OLDPWD = ", oldpwd->value);
		entry = ft_strjoin("[HIST] ", tmp);
		add_history(entry);
		free(tmp);
		free(entry);
	}
}

//  Crea entorno de prueba con HOME y PWD
t_map	*create_test_env(const char *home_path)
{
	t_map	*map;
	char	*cwd;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);

	map->capacity = 4;
	map->size = 0;
	map->keys = ft_calloc(map->capacity, sizeof(t_key *));
	if (!map->keys)
	{
		free(map);
		return (NULL);
	}

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(map->keys);
		free(map);
		return (NULL);
	}

	map->keys[map->size++] = ft_new_key("HOME", home_path);
	map->keys[map->size++] = ft_new_key("PWD", cwd);
	map->keys[map->size] = NULL;

	free(cwd);
	return (map);
}

//  Testea comportamiento del comando cd
void	run_cd_test(char *arg, t_map *env)
{
	t_data	data;
	char	*before = NULL;
	char	*after = NULL;

	before = getcwd(NULL, 0);
	if (!before)
	{
		perror("getcwd failed (before)");
		return;
	}

	data.argv = ft_calloc(3, sizeof(char *));
	data.argv[0] = ft_strdup("cd");
	data.argv[1] = arg ? ft_strdup(arg) : NULL;
	data.argv[2] = NULL;
	data.env = env;
	data.argc = arg ? 2 : 1;
	data.fdout = 1;

	printf("\n🟡 Test: cd %s\n", arg ? arg : "(no arg)");

	ft_cd(&data, before);

	after = getcwd(NULL, 0);
	if (after && strcmp(before, after) != 0)
		printf("✅ CD OK: %s → %s\n", before, after);
	else if (!after || access(after, F_OK) != 0)
		printf("❌ CD ERROR: %s → %s\n", before, arg ? arg : "(null)");
	else
		printf("🟡 CD NO CAMBIO: sigue en %s\n", before);

	free(before);
	free(after);
	if (data.argv)
	{
		if (data.argv[0]) free(data.argv[0]);
		if (data.argv[1]) free(data.argv[1]);
		free(data.argv);
	}
}

int	main(void)
{
	t_map *env = create_test_env(getenv("HOME"));

	run_cd_test(".", env);
	run_cd_test("..", env);
	run_cd_test("/", env);
	run_cd_test(NULL, env);
	run_cd_test("no_such_path", env);

	log_env_change(env);     // ✅ Historial readline
	debug_print_keys(env);   // ✅ Dump visual por consola
	ft_free_map(env);        // ✅ Limpieza total

	return (0);
}