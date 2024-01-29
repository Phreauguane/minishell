/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:02:30 by larz              #+#    #+#             */
/*   Updated: 2024/01/29 18:23:54 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_prm	*create_prm(char *str)
{
	t_prm	*out;

	out = malloc(sizeof(t_prm));
	if (out)
		out->str = str;
	if (out)
		out->next = NULL;
	return (out);
}

void	add_prm(t_prm **prms, char *prm)
{
	t_prm	*p;

	if (*prms == NULL)
	{
		*prms = create_prm(prm);
		return ;
	}
	p = *prms;
	while (p->next)
		p = p->next;
	p->next = create_prm(prm);
}

void	free_prms(t_prm **prms)
{
	if (*prms == NULL)
		return ;
	if ((*prms)->next != NULL)
		free_prms(&((*prms)->next));
	free((*prms)->str);
	free(*prms);
	*prms = NULL;
}
