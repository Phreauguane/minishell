/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:02:19 by jde-meo           #+#    #+#             */
/*   Updated: 2024/02/08 20:14:20 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int run(t_pipeline *ppl, char **envp)
{
	int		stat1;
	pid_t	child1;

    if (ppl->cmd == NULL)
        return (0);
    if (ft_strncmp(ppl->cmd, "exit", ft_strlen(ppl->cmd) + 1) == 0)
    {
        ft_printf("exit\n");
        free_cmd(ppl);
        exit(0);
    }
	child1 = fork();
	if (child1 < 0)
		return (-1);
	if (child1 == 0)
		execute(ppl, envp);
	if (ppl->fd_in != 0)
		close(ppl->fd_in);
	if (ppl->fd_out != 1)
		close(ppl->fd_out);
	//write(2, "waiting..\n", 11);
	waitpid(child1, &stat1, 0);
	//write(2, "Done!\n", 6);
    return (0);
}
