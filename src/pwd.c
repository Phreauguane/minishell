/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:12:15 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/25 12:15:36 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	run_raw(t_pipeline *ppl, char **envp)
{
	int		stat1;
	pid_t	child1;

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

int	pwd(char **envp)
{
	char	*wd;

	wd = get_env_value("PWD", envp);
	if (wd)
		ft_printf("%s\n", wd);
	else
		return (-1);
	return (0);
}
