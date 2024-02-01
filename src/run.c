/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:02:19 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/01 18:36:52 by jde-meo          ###   ########.fr       */
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
		execute(ppl, 0, 1, envp);
	waitpid(child1, &stat1, 0);
    return (0);
}
