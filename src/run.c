/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:02:19 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/06 17:40:40 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int run(t_pipeline **ppl, char **envp)
{
	int		stat1;
	pid_t	child1;

    if ((*ppl)->cmd == NULL)
        return (0);
    if (ft_strncmp((*ppl)->cmd, "exit", ft_strlen((*ppl)->cmd) + 1) == 0)
    {
        ft_printf("exit\n");
        free_ppl(ppl);
        exit(0);
    }
	child1 = fork();
	if (child1 < 0)
		return (-1);
	if (child1 == 0)
		execute(ppl, envp);
	waitpid(child1, &stat1, 0);
    return (0);
}
