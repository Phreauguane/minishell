/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:02:19 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/10 18:50:21 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	comp_cmd(char *cmd, char *builtin)
{
	return (ft_strncmp(cmd, builtin, ft_strlen(cmd) + 1) == 0);
}

int	run_builtin(t_pipeline *ppl, char **envp)
{
	if (ppl->cmd == NULL)
		return (1);
	else if (comp_cmd(ppl->cmd, "exit"))
    {
        ft_printf("exit\n");
        free_cmd(ppl);
        exit(0);
    }
	else if (comp_cmd(ppl->cmd, "cd"))
		g_exec = cd(ppl, envp);
	else
		return (0);
	return (1);
}

char	*run_cmd(char *cmd, char **envp)
{
	t_pipeline	*ppl;
	int			pipe_fd[2];

	ppl = NULL;
	pipe(pipe_fd);
	add_ppl(&ppl)->cmd = cmd;
	ppl->fd_out = pipe_fd[1];
	run(ppl, envp);
	return (get_next_line(pipe_fd[0]));
}

void    run(t_pipeline *ppl, char **envp)
{
	int		stat1;
	pid_t	child1;

	if (run_builtin(ppl, envp))
		return ;
	child1 = fork();
	if (child1 < 0)
		return ;
	if (child1 == 0)
		execute(ppl, envp);
	if (ppl->fd_in != 0)
		close(ppl->fd_in);
	if (ppl->fd_out != 1)
		close(ppl->fd_out);
	waitpid(child1, &stat1, 0);
    g_exec = stat1;
}

void    run_pipeline(t_pipeline *ppl, int stdin_bk, char **envp)
{
    t_pipeline  *p;
    
	p = ppl;
	while (p)
	{
		dup2(stdin_bk, STDIN_FILENO);
		if (p->error == 0)
			run(p, envp);
		p = p->next;
	}
}