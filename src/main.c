/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:29:08 by larz              #+#    #+#             */
/*   Updated: 2024/02/11 22:36:44 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_sig;
int g_exec;
int	g_stdin;

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

void	config(char **envp)
{
	struct sigaction	s;

	open_history(envp);
	update_shlvl(envp);
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

void	print_pipeline(t_pipeline *ppl)
{
	t_prm	*p;

	while (ppl)
	{
		ft_printf("PIPELINE : %p\nCOMMAND : %s\n", ppl, ppl->cmd);
		ft_printf("PARAMS :\n");
		p = ppl->prm;
		while (p)
		{
			ft_printf("\t[%s]\n", p->str);
			p = p->next;
		}
		ppl = ppl->next;
	}
	ft_printf("PIPELINE : %p\n", ppl);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	char		**env;
	t_pipeline	*ppl;

	g_sig = -1;
	g_stdin = dup(STDIN_FILENO);
	env = dup_envp(envp);
	config(env);
	while ((ac && av) || 1)
	{
		line = readline(build_input(env));
		history(line);
		dup2(g_stdin, STDIN_FILENO);
		if (!check_input(line))
			continue ;
		ppl = parse(line, env);
		free(line);
		ft_printf(COLOR);
        run_pipeline(ppl, &env);
	}
	ft_free_split(env);
	cleanup_history();
}
