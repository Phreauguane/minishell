/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:36:47 by larz              #+#    #+#             */
/*   Updated: 2024/03/25 12:42:00 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_pipe(t_pipeline **ppl, char **s, int *mode)
{
	int	pipe_fd[2];

	if (*mode == MODE_NEW_CMD)
		exit_handler("parsing error near token |", NULL, 0, 2);
	pipe(pipe_fd);
	if (get_last(*ppl)->fd_out == STDOUT_FILENO)
		get_last(*ppl)->fd_out = pipe_fd[1];
	else
		close(pipe_fd[1]);
	add_ppl(ppl);
	get_last(*ppl)->fd_in = pipe_fd[0];
	*mode = MODE_NEW_CMD;
	(*s)++;
}

int	throw_error(t_pipeline *ppl, int err)
{
	if (err == ERROR_PARSING)
		exit_handler("Parsing error", NULL, 0, 2);
	if (err == ERROR_NO_CMD)
		exit_handler("Parsing error", "No command found", 0, 2);
	if (err == ERROR_INVALID_CMD)
		exit_handler("Command not found", ppl->cmd, 0, 127);
	return (err);
}

int	verif_command(t_pipeline *ppl, char **envp)
{
	char		*cmd;

	if (!ppl || ppl->error)
		return (ERROR_PARSING);
	if (ppl->cmd == NULL || ppl->cmd[0] == '\0')
		return (ERROR_NO_CMD);
	cmd = get_exec(ppl->cmd, envp);
	if (!is_builtin(ppl) && access(cmd, F_OK | X_OK) != 0)
		return (free2(cmd), ERROR_INVALID_CMD);
	return (free2(cmd), NO_ERROR);
}

int	verif_pipeline(t_pipeline **ppl, char **envp)
{
	t_pipeline	*p;

	if (!ppl || !(*ppl))
		return (0);
	p = *ppl;
	while (p)
	{
		if (throw_error(p, verif_command(p, envp)) != NO_ERROR)
			return (1);
		p = p->next;
	}
	return (0);
}
