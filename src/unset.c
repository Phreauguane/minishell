/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:52:41 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/06 20:57:46 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_var_i(char *var, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (strncmp(var, envp[i], ft_strlen(var)) == 0)
			return (i);
	return (-1);
}

void	remove_env_var(char *var, char **envp)
{
	int	i;

	i = find_var_i(var, envp);
	if (i < 0)
		return ;
	free2(envp[i]);
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
}

int	unset(t_pipeline *ppl, char **envp)
{
	t_prm	*p;

	p = ppl->prm;
	while (p && p->str)
	{
		remove_env_var(p->str, envp);
		p = p->next;
	}
	return (0);
}

void    print_pipeline(t_pipeline *ppl)
{
    t_prm    *p;

    while (ppl)
    {
        ft_printf("PIPELINE : %p\nCOMMAND : %s\n", ppl, ppl->cmd);
		ft_printf("INPUT : %d\nOUTPUT : %d\nERROR : %d\n", ppl->fd_in,
			ppl->fd_out, ppl->error);
        ft_printf("PARAMS :\n");
        p = ppl->prm;
        while (p)
        {
            ft_printf("\t[%s]\n", p->str);
            p = p->next;
        }
        ppl = ppl->next;
    }
    ft_printf("PIPELINE : %p\n", ppl);
}
