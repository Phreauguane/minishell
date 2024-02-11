/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:47:24 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/11 22:50:45 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cd(t_pipeline *ppl, char **envp)
{
	char	*path;
	char	*pwd;
    int		exec;

	if (!(ppl->prm) || !(ppl->prm->str))
		path = get_env_value("HOME", envp);
	else if (ppl->prm->next != NULL)
	{
        ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	else
		path = ppl->prm->str;
    exec = chdir(path);
    if (exec == -1)
		ft_printf("minishell: cd: %s: no such file or directory\n", path);
	pwd = run_cmd("pwd", envp);
	path = str_adds(NULL, pwd, ft_strlen(pwd) - 1);
	if (exec == 0)
		set_env_value("PWD", path, envp);
	free(path);
	free(pwd);
	return (exec);
}
