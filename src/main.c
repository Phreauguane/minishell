/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:29:08 by larz              #+#    #+#             */
/*   Updated: 2024/01/30 16:38:50 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char		*line;
	t_pipeline	*cmd;
	t_prm		*p;

	while (1)
	{
		line = readline("8=>");
		printf("line : %s\n", line);
		cmd = parse(line);
		printf("Command: %s\n", cmd->cmd);
		printf("Parameters:\n");
		p = cmd->prm;
		while (p)
		{
			printf("\t<%s>\n", p->str);
			p = p->next;
		}
		free(line);
		free(cmd->cmd);
		free_prms(&(cmd->prm));
	}
}