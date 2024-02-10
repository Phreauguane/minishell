/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:30:32 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/10 18:15:02 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char    *get_env_value(char *var, char **envp)
{
	int	i;

	i = -1;
	if (strncmp(var, "?", ft_strlen(var) + 1) == 0)
		return (ft_itoa(g_exec));
	while (envp[++i])
		if (strncmp(var, envp[i], ft_strlen(var)) == 0)
			return (ft_strchr(envp[i], '=') + 1);
	return (NULL);
}

void	set_env_value(char *var, char *value, char **envp)
{
	int		i;
	char	*new_val;

	i = -1;
	new_val = str_adds(NULL, var, ft_strlen(var));
	new_val = str_addc(new_val, '=');
	new_val = str_adds(new_val, value, ft_strlen(value));
	while (envp[++i])
		if (strncmp(var, envp[i], ft_strlen(var)) == 0)
			envp[i] = new_val;
}
