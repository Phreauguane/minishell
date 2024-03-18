/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:28:49 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/18 14:35:15 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	verif_parameter(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	exit_builtin(t_pipeline *ppl)
{
	ft_printf("exit\n");
	if (ppl->prm && ppl->prm->str && 
		verif_parameter(ppl->prm->str) && ppl->prm->next == NULL)
	{
		g_exec = ft_atoi(ppl->prm->str);
		ft_printf("atoi out : %d\n", g_exec);
	}
	else if (ppl->prm && ppl->prm->str && !verif_parameter(ppl->prm->str))
		exit_handler("exit", "numeric argument required", 0, 2);
	else if (ppl->prm && ppl->prm->next != NULL)
		return(exit_handler("exit", "too many arguments", 0, 1));
	exit_minishell(0);
}
