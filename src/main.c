/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:29:08 by larz              #+#    #+#             */
/*   Updated: 2024/01/29 18:18:52 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char		*line;
	t_command	cmd;
	t_prm		*p;

	while (1)
	{
		line = readline("8=>");
		printf("line : %s\n", line);
		cmd = parse(line);
		printf("Command: %s\n", cmd.cmd);
		printf("Parameters:\n");
		p = cmd.prm;
		while (p)
		{
			printf("\t<%s>\n", p->str);
			p = p->next;
		}
		free(line);
		free(cmd.cmd);
		free_prms(&(cmd.prm));
	}
}