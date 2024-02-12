/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:34:42 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/12 17:08:00 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	echo(t_pipeline *ppl)
{
	int		endl;
	t_prm	*prm;

	endl = 1;
	if (ppl->prm == NULL)
		ft_printf("\n");
	if (ppl->prm == NULL)
		return (0);
	if (ppl->prm->str && ft_strncmp(ppl->prm->str, "-n", 3) == 0)
		endl = 0;
	prm = ppl->prm->next;
	if (endl)
		prm = ppl->prm;
	while (prm)
	{
		if (prm->str)
			ft_printf("%s", prm->str);
		if (prm->next && prm->str && ft_strlen(prm->str)
			&& prm->next->str && ft_strlen(prm->next->str))
			ft_printf(" ");
		prm = prm->next;	
	}
	if (endl)
		ft_printf("\n");
	return (0);
}
