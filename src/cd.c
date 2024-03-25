/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:47:24 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/25 12:05:15 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cd(t_pipeline *ppl, char **envp)
{
	char	*path;
	char	*pwd;
	int		exec;

	path = NULL;
	if (!(ppl->prm) || !(ppl->prm->str) || !ft_strncmp(ppl->prm->str, "~", 2))
		path = get_env_value("HOME", envp);
	if (ppl->prm && ppl->prm->next != NULL)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (!path)
		path = ppl->prm->str;
	exec = chdir(path);
	if (exec == -1)
		ft_printf("minishell: cd: %s: no such file or directory\n", path);
	pwd = run_cmd("pwd", envp);
	path = str_adds(NULL, pwd, ft_strlen(pwd) - 1);
	if (exec == 0)
		set_env_value("PWD", path, envp);
	free2(path);
	free2(pwd);
	return (exec);
}
