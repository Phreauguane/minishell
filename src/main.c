/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:29:08 by larz              #+#    #+#             */
/*   Updated: 2024/02/01 18:52:07 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	g_sig;

void	handler(int sig)
{
	g_sig = sig;
	if (g_sig == SIGINT)
	{
		ft_printf("\n"BOLD_GREEN"8=> "BOLD_CYAN);
		g_sig = -1;
	}
}

void	config_signals(void)
{
	signal(SIGINT, handler); 	// CTRL C
	signal(SIGQUIT, handler);	// CTRL /
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_pipeline	*ppl;

	(void)ac;
	(void)av;
	g_sig = -1;
	config_signals();
	while (1)
	{
		line = readline(BOLD_GREEN"8=> "BOLD_CYAN);
		ppl = parse(line);
		ft_printf(BOLD_PURPLE);
		free(line);
		run(&ppl, envp);
	}
}
