/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:36:08 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/08 20:14:27 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H'
			&& envp[i][4] == '=')
			return (&(envp[i][5]));
		i++;
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_exec(char *cmd, char **envp)
{
	char	**paths;
	char	*exec;
	int		i;

	paths = ft_split(get_paths(envp), ':');
	i = -1;
	while (paths[++i] && cmd)
	{
		paths[i] = str_addc(paths[i], '/');
		paths[i] = str_adds(paths[i], cmd, ft_strlen(cmd));
		if (access(paths[i], F_OK | X_OK) == 0)
		{
			exec = ft_strdup(paths[i]);
			free_tab(paths);
			return (exec);
		}
	}
	free_tab(paths);
	return (cmd);
}

char    **build_prms(t_pipeline *ppl)
{
    t_prm   *p;
    int     size;
    char    **tab;

    size = 0;
    p = ppl->prm;
    while (p && ++size >= 0)
        p = p->next;
    tab = malloc(sizeof(char *) * (size + 2));
    tab[size + 1] = NULL;
    size = 0;
    p = ppl->prm;
	tab[0] = ppl->cmd;
    while (p)
    {
        tab[++size] = p->str;
        p = p->next;
    }
    return (tab);
}

void	execute(t_pipeline *ppl, char **envp)
{
	char	**cmd_args;
	char	*exec;

	dup2(ppl->fd_in, STDIN_FILENO);
	dup2(ppl->fd_out, STDOUT_FILENO);
	if (ppl->fd_in != 0)
		close(ppl->fd_in);
	if (ppl->fd_out != 1)
		close(ppl->fd_out);
	if (ppl->cmd == NULL)
		exit(0);
	cmd_args = build_prms(ppl);
	exec = get_exec(ppl->cmd, envp);
	//write(2, "Executing command\n", 19);
	execve(exec, cmd_args, envp);
	//write(2, "Done 2!\n", 8);
	exit_handler("command not found", exec, 0, -1);
}
