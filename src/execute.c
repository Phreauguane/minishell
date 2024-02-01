/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:36:08 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/01 17:51:52 by jde-meo          ###   ########.fr       */
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
    tab[size] = NULL;
    size = 0;
    p = ppl->prm;
	tab[0] = ppl->cmd;
    while (p && ++size >= 0)
    {
        tab[size] = p->str;
        p = p->next;
    }
    return (tab);
}

void	execute(t_pipeline **ppl, int ifd, int ofd, char **envp)
{
	char	**cmd_args;
	char	*exec;

	dup2(ifd, STDIN_FILENO);
	dup2(ofd, STDOUT_FILENO);
	if ((*ppl)->cmd == NULL)
		exit(0);
	cmd_args = build_prms(*ppl);
	exec = get_exec((*ppl)->cmd, envp);
	if (execve(exec, cmd_args, envp) == -1)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(exec, STDERR_FILENO);
		exit(-1);
	}
}
