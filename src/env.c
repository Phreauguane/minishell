/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:30:32 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/25 13:25:47 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_value(char *var, char **envp)
{
	int	i;

	i = -1;
	if (!var || !var[0])
		return ("\0");
	if (strncmp(var, "?", ft_strlen(var) + 1) == 0)
		return (ft_itoa(g_exec));
	while (envp[++i])
	{
		if (strncmp(var, envp[i], ft_strlen(var)) == 0)
		{
			if (ft_strchr(envp[i], '=') != NULL)
				return (ft_strchr(envp[i], '=') + 1);
			return ("\0");
		}
	}
	return ("\0");
}

int	find_var(char *var, char **envp)
{
	int	i;

	i = -1;
	if (!var || !var[0])
		return (0);
	while (envp[++i])
		if (strncmp(var, envp[i], ft_strlen(var)) == 0)
			return (1);
	return (0);
}

void	set_env_value(char *var, char *value, char **envp)
{
	int		i;
	char	*new_val;

	i = -1;
	if (!var || !var[0])
		return ;
	new_val = str_adds(NULL, var, ft_strlen(var));
	if (value)
	{
		new_val = str_addc(new_val, '=');
		new_val = str_adds(new_val, value, ft_strlen(value));
	}
	while (envp[++i])
	{
		if (strncmp(var, envp[i], ft_strlen(var)) == 0)
		{
			free2(envp[i]);
			envp[i] = new_val;
		}
	}
}

void	update_shlvl(char **envp)
{
	char	*value;
	char	*new;

	value = get_env_value("SHLVL", envp);
	new = ft_itoa(ft_atoi(value) + 1);
	set_env_value("SHLVL", new, envp);
	free2(new);
}

int	env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp[i])
		ft_printf("%s\n", envp[i++]);
	return (0);
}
