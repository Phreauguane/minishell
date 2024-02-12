/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:02:19 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/12 17:56:33 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*run_cmd(char *cmd, char **envp)
{
	t_pipeline	*ppl;
	int			pipe_fd[2];

	ppl = NULL;
	pipe(pipe_fd);
	add_ppl(&ppl)->cmd = cmd;
	ppl->fd_out = pipe_fd[1];
	run_raw(ppl, envp);
	free(ppl);
	return (get_next_line(pipe_fd[0]));
}

void    run(t_pipeline *ppl, char ***envp)
{
	int		stat1;
	pid_t	child1;

	if (run_builtin(ppl, envp))
		return ;
	child1 = fork();
	if (child1 < 0)
		return ;
	if (child1 == 0)
		execute(ppl, *envp);
	if (ppl->fd_in != 0)
		close(ppl->fd_in);
	if (ppl->fd_out != 1)
		close(ppl->fd_out);
	waitpid(child1, &stat1, 0);
    g_exec = stat1;
}

void    run_pipeline(t_pipeline *ppl, char ***envp)
{
    t_pipeline  *p;
    
	p = ppl;
	while (p)
	{
		dup2(g_stdin, STDIN_FILENO);
		if (p->error == 0)
			run(p, envp);
		p = p->next;
	}
}