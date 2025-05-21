/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:53:36 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/21 19:20:41 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//comprobacion de señales y no abre correctamente

static void	sigquit_handler(int sig)
{
	(void)sig;
	write(1, "\033[2D  \033[2D", 10);
}

static void	ft_child_write_hd(t_data *data, char *dl, int hd)
{
	char	*str;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str)
			break ;
		if (!ft_strncmp(str, dl, ft_strlen(dl)) && str[ft_strlen(dl)] == '\n')
		{
			free(str);
			str = NULL;
			break ;
		}
		ft_putstr_fd(str, hd);
		free(str);
		str = NULL;
	}
	close(hd);
	ft_free_resources(data);
	exit(0);
}

static void	fork_process(t_data *data, pid_t pid, int hd, char *dl)
{
	if (pid == -1)
	{
		ft_putstr_fd("Fork error\n", 2);
		close(hd);
		return ;
	}
	if (pid == 0)
		ft_child_write_hd(data, dl, hd);
}

void	ft_write_hd(t_data *data, char *dl)
{
	pid_t	pid;
	int		status;
	int		hd;

	ft_setup_parent_signals();
	hd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (hd == -1)
	{
		ft_putstr_fd(FILE_ERR, data->fdout);
		data->status = 1;
		return ;
	}
	pid = fork();
	fork_process(data, pid, hd, dl);
	close(hd);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		data->status = 130;
	else
		data->status = 0;
}

void	ft_here_doc(t_data *data, char *dl)
{
	int		nw_fd;

	g_block = 3;
	if (!dl)
	{
		ft_putstr_fd("bash: syntax error, unexpected token\n", data->fdout);
		data->status = 1;
		return ;
	}
	ft_write_hd(data, dl);
	nw_fd = open(".tmp", O_RDONLY);
	data->fdin = nw_fd;
	unlink(".tmp");
	g_block = 0;
}
