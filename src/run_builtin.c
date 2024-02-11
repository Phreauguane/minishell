/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:44:46 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/11 21:43:28 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	comp_cmd(char *cmd, char *builtin)
{
	return (ft_strncmp(cmd, builtin, ft_strlen(cmd) + 1) == 0);
}

int	run_builtin(t_pipeline *ppl, char ***envp)
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
		g_exec = cd(ppl, *envp);
	else if (comp_cmd(ppl->cmd, "env"))
		g_exec = env(*envp);
	else if (comp_cmd(ppl->cmd, "echo"))
		g_exec = echo(ppl);
	else if (comp_cmd(ppl->cmd, "pwd"))
		g_exec = pwd(*envp);
	else if (comp_cmd(ppl->cmd, "export"))
		g_exec = export(ppl, envp);
	else
		return (0);
	return (1);
}
