/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:44:46 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/05 15:52:12 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	comp_cmd(char *cmd, char *builtin)
{
	return (ft_strncmp(cmd, builtin, ft_strlen(cmd) + 1) == 0);
}

int	is_builtin(t_pipeline *ppl)
{
	if (comp_cmd(ppl->cmd, "cd")
		|| comp_cmd(ppl->cmd, "env")
		|| comp_cmd(ppl->cmd, "echo")
		|| comp_cmd(ppl->cmd, "pwd")
		|| comp_cmd(ppl->cmd, "export")
		|| comp_cmd(ppl->cmd, "unset"))
		return (1);
	return (0);
}

void	run_builtin_cmd(t_pipeline *ppl, char ***envp)
{
	if (comp_cmd(ppl->cmd, "cd"))
		g_exec = cd(ppl, *envp);
	else if (comp_cmd(ppl->cmd, "env"))
		g_exec = env(*envp);
	else if (comp_cmd(ppl->cmd, "echo"))
		g_exec = echo(ppl);
	else if (comp_cmd(ppl->cmd, "pwd"))
		g_exec = pwd(*envp);
	else if (comp_cmd(ppl->cmd, "export"))
		g_exec = export(ppl, envp);
	else if (comp_cmd(ppl->cmd, "unset"))
		g_exec = unset(ppl, *envp);
}

int	run_builtin(t_pipeline *ppl, char ***envp)
{
	int	stdin_bk;
	int	stdout_bk;

	if (ppl->cmd == NULL)
		return (1);
	else if (comp_cmd(ppl->cmd, "exit"))
    {
        ft_printf("exit\n");
        free_cmd(ppl);
        return (exit_minishell(1));
    }
	if (!is_builtin(ppl))
		return (0);
	stdin_bk = dup(STDIN_FILENO);
	stdout_bk = dup(STDOUT_FILENO);
	dup2(ppl->fd_in, STDIN_FILENO);
	dup2(ppl->fd_out, STDOUT_FILENO);
	run_builtin_cmd(ppl, envp);
	if (ppl->fd_in != 0)
		close(ppl->fd_in);
	if (ppl->fd_out != 1)
		close(ppl->fd_out);
	dup2(stdin_bk, STDIN_FILENO);
	dup2(stdout_bk, STDOUT_FILENO);
	return (1);
}

void	free2(void *ptr)
{
	if (ptr)
		free(ptr);
}
