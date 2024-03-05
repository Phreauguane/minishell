/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:02:19 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/05 15:29:37 by jde-meo          ###   ########.fr       */
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
	free2(ppl);
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
	free_ppl(&ppl);
}

char	*run_fullcmd(char *cmd, char **envp)
{
	t_pipeline	*ppl;
	int			pipe_fd[2];
	char		*files;
	char		*line;
	int			bk;

	bk = g_exec;
	files = NULL;
	ppl = NULL;
	pipe(pipe_fd);
	add_ppl(&ppl)->cmd = cmd;
	ppl->fd_out = pipe_fd[1];
	run_raw(ppl, envp);
	free2(ppl);
	line = get_next_line(pipe_fd[0]);
	while (line)
	{
		files = str_adds(files, line, ft_strlen(line));
		free2(line);
		line = get_next_line(pipe_fd[0]);
	}
	g_exec = bk;
	return (files);
}

char	*run_fullcmdprm(char *dir,char *cmd, char **envp)
{
	t_pipeline	*ppl;
	int			pipe_fd[2];
	char		*files;
	char		*line;
	int			bk;

	files = NULL;
	ppl = NULL;
	pipe(pipe_fd);
	add_ppl(&ppl)->cmd = cmd;
	add_prm(&(ppl->prm), str_adds(NULL, dir, ft_strlen(dir)));
	ppl->fd_out = pipe_fd[1];
	run3(ppl, &bk, envp);
	free2(ppl);
	line = get_next_line(pipe_fd[0]);
	while (line && line[0])
	{
		if (bk == 0)
			files = str_adds(files, line, ft_strlen(line));
		free2(line);
		line = get_next_line(pipe_fd[0]);
	}
	return (files);
}
