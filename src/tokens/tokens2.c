
#include "minishell.h"

int	is_op(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

static int	is_redirection(char *token)
{
	return (!ft_strcmp(token, ">") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "<") || !ft_strcmp(token, "<<"));
}

static int	fill_cmd_args(t_token *cmd, char **tokens, int i)
{
	int	argi;

	argi = 0;
	if (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
		cmd->cmd = ft_strdup(tokens[i++]);
	while(tokens[i] && ft_strcmp(tokens[i], "|") != 0)
	{
		printf("Token[%d]: \"%s\"\n", i, tokens[i]);
		if(is_redirection(tokens[i]))
		{
			i += 2;
			continue ;
		}
		cmd->cargs[argi++] = ft_strdup(tokens[i++]);
	}
	cmd->cargs[argi] = NULL;
	return (i);
}

t_token	**tokenize_command(char **tokens)
{
	t_token	**cmds;
	int		i;
	int		cmdi;

	cmds = (t_token **)ft_calloc(20, sizeof(t_token *));
	i = 0;
	cmdi = 0;
	while (tokens[i])
	{
		cmds[cmdi] = ft_calloc(1, sizeof(t_token));
		cmds[cmdi]->cargs = ft_calloc(20, sizeof(char *));
		i = fill_cmd_args(cmds[cmdi], tokens, i);
		if (tokens[i] && !ft_strcmp(tokens[i], "|"))
			i++;
		cmdi++;
	}
	cmds[cmdi] = NULL;
	return (cmds);
}
