/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:19:16 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/11 20:44:41 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_vars(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**dup_envp(char **envp)
{
	int		i;
	char	**out;

	i = env_vars(envp);
	out = malloc(sizeof(char *) * (i + 1));
	out[i] = NULL;
	while (--i >= 0)
		out[i] = ft_strdup(envp[i]);
	return (out);
}

void	append_env_var(char ***envp, char *var, char *val)
{
	int		i;
	char	*v;
	char	**new;

	i = env_vars(*envp) + 1;
	v = str_adds(NULL, var, ft_strlen(var));
	if (val)
	{
		v = str_addc(v, '=');
		v = str_adds(v, val, ft_strlen(val));
	}
	new = malloc(sizeof(char *) * (i + 1));
	new[i--] = NULL;
	new[i] = v;
	while (--i >= 0)
		new[i] = (*envp)[i];
	free(*envp);
	*envp = new;
}

void	sort_envp(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (envp[++i])
	{
		j = i;
		while (envp[++j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i]) + ft_strlen(envp[j])) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
		}
	}
}

int	export(t_pipeline *ppl, char ***envp)
{
	t_prm	*p;
	char	*val;
	int		i;

	p = ppl->prm;
	i = -1;
	if (p == NULL || p->str == NULL)
		sort_envp(*envp);
	while ((p == NULL || p->str == NULL) && (*envp)[++i])
		ft_printf("%s\n", (*envp)[i]);
	while (p && p->str)
	{
		val = ft_strchr(p->str, '=');
		if (val)
			val[0] = '\0';
		if (val)
			val++;
		if (find_var(p->str, *envp) == 0)
			append_env_var(envp, p->str, val);
		else
			set_env_value(p->str, val, *envp);
		p = p->next;
	}
	return (0);
}
