#include "minishell.h"

typedef struct s_test_case {
	const char	*desc;
	char		**argv_raw;
	const char	*expected;
}	t_test_case;

t_map	*create_test_env(void)
{
	t_map	*env = ft_calloc(1, sizeof(t_map));
	env->keys = ft_calloc(4, sizeof(t_key *));
	env->keys[0] = ft_new_key("HOME", ft_strdup("/home/fracurul"));
	env->keys[1] = ft_new_key("USER", ft_strdup("fracurul"));
	env->keys[2] = ft_new_key("SHELL", ft_strdup("/bin/bash"));
	env->keys[3] = NULL;
	env->size = 3;
	env->capacity = 4;
	return (env);
}

void	free_test_env(t_map *env)
{
	if (!env)
		return;
	ft_free_keys(env->keys);
	free(env);
}

char	**dup_argv(char **argv_raw)
{
	int		i = 0;
	while (argv_raw[i])
		i++;
	char **copy = ft_calloc(i + 1, sizeof(char *));
	for (int j = 0; j < i; j++)
		copy[j] = ft_strdup(argv_raw[j]);
	return (copy);
}

void	run_echo_test(t_test_case test)
{
	t_data	data;
	int		fd[2];
	char	buffer[1024] = {0};
	int		saved_stdout;

	char **argv = dup_argv(test.argv_raw);
	data.argv = argv;
	data.env = create_test_env();
	data.fdout = STDOUT_FILENO;
	data.argc = 0;
	while (argv[data.argc])
		data.argc++;

	pipe(fd);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);

	ft_echo(&data);

	fflush(stdout);
	read(fd[0], buffer, sizeof(buffer) - 1);
	dup2(saved_stdout, STDOUT_FILENO);
	close(fd[0]);
	close(saved_stdout);

	printf("\n🛠️  Test: %s\n", test.desc);
	for (int j = 0; argv[j]; j++)
		printf("   ARG[%d]: %s\n", j, argv[j]);
	printf("🔹 Test: %s\n", test.desc);
	printf("  Esperado: \"%s\"\n", test.expected);
	printf("  Recibido: \"%s\"\n", buffer);

	if (strcmp(buffer, test.expected) == 0)
		printf("✅ PASSED\n");
	else
		printf("❌ FAILED\n");

	for (int i = 0; argv[i]; i++)
		free(argv[i]);
	free(argv);
	free_test_env(data.env);
}

int	main(void)
{
	t_test_case tests[] = {
		{ "echo sin argumentos", (char *[]){"echo", NULL}, "\n" },
		{ "echo texto normal", (char *[]){"echo", "hola", "mundo", NULL}, "hola mundo\n" },
		{ "echo -n simple", (char *[]){"echo", "-n", "hola", "mundo", NULL}, "hola mundo" },
		{ "echo -n múltiple", (char *[]){"echo", "-n", "-n", "hola", NULL}, "hola" },
		{ "echo -nnnn", (char *[]){"echo", "-nnnn", "boom", NULL}, "boom" },
		{ "echo -n -x hola", (char *[]){"echo", "-n", "-x", "hola", NULL}, "-x hola\n" },
		{ "echo vacío + -n", (char *[]){"echo", "-n", " ", NULL}, "" },// hay que poner espacio en blanco porque echo espera si o si un contenido no se puede pasar ni NULL ni '\0'
		{ "echo con espacio", (char *[]){"echo", "hola,", "shell", NULL}, "hola, shell\n" },
		{ "echo $HOME", (char *[]){"echo", "$HOME", NULL}, "/home/fracurul\n" },
		{ "echo $USER", (char *[]){"echo", "$USER", NULL}, "fracurul\n" },
		{ "echo mezcla texto + $USER", (char *[]){"echo", "Hi,", "$USER", NULL}, "Hi, fracurul\n" },
		{ "echo -n $SHELL", (char *[]){"echo", "-n", "$SHELL", NULL}, "/bin/bash" },
		{ NULL, (char *[]) { NULL }, NULL } // Sentinel para evitar bucles infinitos
	};

	// Debug inicial para verificar el sentinel
	for (int i = 0; i < 20; i++)
	{
		if (tests[i].desc == NULL && tests[i].argv_raw == NULL)
		{
			printf("DEBUG: Test[%d]: (FIN DETECTADO CORRECTAMENTE)\n", i);
			break;
		}
		printf("DEBUG: Test[%d]: desc = %p, argv_raw = %p\n", i, (void *)tests[i].desc, (void *)tests[i].argv_raw);
	}

	for (int i = 0; tests[i].desc != NULL; i++)
		run_echo_test(tests[i]);


	return (0);
}
