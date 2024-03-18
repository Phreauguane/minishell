/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:42:47 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/18 13:19:06 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sig;

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
	g_sig = -1;
	ft_bzero(&s, sizeof(s));
	s.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s, NULL);
	signal(SIGINT, handler);
}

int	check_input(char *line)
{
	int	i;

	i = 0;
	if (g_sig == SIGINT)
	{
		g_sig = -1;
		free2(line);
		return (0);
	}
	if (line == NULL && g_sig != SIGINT)
	{
		ft_printf("exit\n");
		free2(line);
		exit_minishell(0);
		return (0);
	}
	while (line && ft_isspace(line[i]))
		i++;
	if (line == NULL || line[0] == '\0' || line[i] == '\0')
		return (0);
	return (1);
}
