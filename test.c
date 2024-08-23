#include  "minishell.h"

int main()
{
	char	*input;

	printf("ctrl+D para salir\n");
	while ((input = readline("Write something") != NULL)
	{
		if (input && *input)
		{
			add_history(input);
		}
		else
		{
		free(inputr);
		break;
		}
	}
	free(input);
	clear_history();
	return (0);
}
