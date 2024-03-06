/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:39:13 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/06 20:52:41 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pipeline	*create_ppl(void)
{
	t_pipeline	*out;

	out = malloc(sizeof(t_pipeline));
    ft_bzero(out, sizeof(t_pipeline));
	out->fd_out = 1;
	return (out);
}

t_pipeline	*add_ppl(t_pipeline **ppl)
{
	t_pipeline	*p;

	if (*ppl == NULL)
	{
		*ppl = create_ppl();
		return (*ppl);
	}
	p = *ppl;
	while (p->next)
		p = p->next;
	p->next = create_ppl();
    return (p->next);
}

void	free_cmd(t_pipeline *ppl)
{
    free2(ppl->cmd);
    free_prms(&(ppl->prm));
	if (ppl->fd_in != 0)
		close(ppl->fd_in);
	if (ppl->fd_out != 1)
		close(ppl->fd_out);
}

void	free_ppl(t_pipeline **ppl)
{
	if (*ppl == NULL)
		return ;
	if ((*ppl)->next != NULL)
		free_ppl(&((*ppl)->next));
	free_cmd(*ppl);
	free2(*ppl);
	*ppl = NULL;
}

t_pipeline	*get_last(t_pipeline *ppl)
{
	if (ppl == NULL)
		return (NULL);
	while (ppl->next)
		ppl = ppl->next;
	return (ppl);
}
