/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:29:08 by larz              #+#    #+#             */
/*   Updated: 2024/03/05 15:50:55 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_exec;
int	g_stdin;
int	g_end;

int	exit_minishell(int out)
{
	g_end = 1;
	return (out);
}

void	exit_handler(char *msg, char *details, int free_msg, int code)
{
	if (msg && details)
		ft_printf("minishell: %s: %s\n", msg, details);
	else if (msg)
		ft_printf("minishell: %s\n", msg);
	if (free_msg)
		free2(msg);
	g_exec = code;
}

void	cleanup(char **env)
{
	ft_free_split(env);
	cleanup_history();
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	char		**env;
	t_pipeline	*ppl;

	g_stdin = dup(STDIN_FILENO);
	env = dup_envp(envp);
	g_end = 0;
	config(env);
	while (g_end != 1 && ((ac && av) || 1))
	{
		line = get_input(build_input(env));
		history(line);
		dup2(g_stdin, STDIN_FILENO);
		if (!check_input(line))
			continue ;
		ppl = parse(line, env);
		free2(line);
		ft_printf(COLOR);
        run_pipeline(ppl, &env);
	}
	cleanup(env);
}
