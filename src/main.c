/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:29:08 by larz              #+#    #+#             */
/*   Updated: 2024/02/10 21:52:38 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_sig;
int g_exec;

void	handler(int sig)
{
	g_sig = sig;
	if (sig == SIGQUIT)
		g_sig = -1;
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		close(0);
	}
}

void	config_signals(void)
{
	struct sigaction	s;
	ft_bzero(&s, sizeof(s));
	s.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s, NULL);
	signal(SIGINT, handler); 	// CTRL C
	
}

int	check_input(char *line)
{
	if (g_sig == SIGINT)
	{
		g_sig = -1;
		return (0);
	}
	if (line == NULL && g_sig != SIGINT)
	{
		ft_printf("exit\n");
		exit (0);
	}
	if (line == NULL)
		return (0);
	return (1);
}

void	exit_handler(char *msg, char *details, int free_msg, int code)
{
	if (msg && details)
		ft_printf("minishell: %s: %s\n", msg, details);
	else if (msg)
		ft_printf("minishell: %s\n", msg);
	if (free_msg && msg)
		free(msg);
	g_exec = code;
}

int	main(int ac, char **av, char **envp)
{
	int			stdin_bk;
	char		*line;
	t_pipeline	*ppl;

	g_sig = -1;
	stdin_bk = dup(STDIN_FILENO);
	config_signals();
	while ((ac && av) || 1)
	{
		line = readline(build_input(envp));
		if (line)
			history(line);
		dup2(stdin_bk, STDIN_FILENO);
		if (!check_input(line))
			continue ;
		ppl = parse(line);
		ft_printf(COLOR);
		free(line);
        run_pipeline(ppl, stdin_bk, envp);
	}
	clear_history();
}
