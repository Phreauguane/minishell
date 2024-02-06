/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:29:08 by larz              #+#    #+#             */
/*   Updated: 2024/02/06 17:38:17 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	g_sig;

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

int	main(int ac, char **av, char **envp)
{
	int			stdin_bk;
	char		*line;
	t_pipeline	*ppl;

	(void)ac;
	(void)av;
	g_sig = -1;
	stdin_bk = dup(STDIN_FILENO);
	config_signals();
	while (1)
	{
		line = readline(build_input(envp));
		dup2(stdin_bk, STDIN_FILENO);
		if (!check_input(line))
			continue ;
		ppl = parse(line);
		ft_printf(BOLD_PURPLE);
		free(line);
		run(&ppl, envp);
	}
}
