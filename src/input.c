/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:21:37 by larz              #+#    #+#             */
/*   Updated: 2024/02/06 17:59:23 by larz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_folder(char **envp)
{
	t_pipeline	*ppl;
	int			pipe_fd[2];
	char		*line;

	ppl = NULL;
	add_ppl(&ppl)->cmd = str_adds(NULL, "pwd", 7);
	if (pipe(pipe_fd) < 0)
		return (NULL);
	ppl->fd_out = pipe_fd[1];
	run(&ppl, envp);
	line = get_next_line(pipe_fd[0]);
	free_ppl(&ppl);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (line);
	
}

char *build_input(char **envp)
{
	t_pipeline	*ppl;
	int			pipe_fd[2];
	char		*out;
	char		*line;

	out = NULL;
	ppl = NULL;
	add_ppl(&ppl)->cmd = str_adds(NULL, "whoami", 7);
	if (pipe(pipe_fd) < 0)
		return (NULL);
	ppl->fd_out = pipe_fd[1];
	run(&ppl, envp);
	line = get_next_line(pipe_fd[0]);
	out = str_adds(out, BOLD_PURPLE"@", ft_strlen(BOLD_PURPLE" | "));
	out = str_adds(out, line, ft_strlen(line) - 1);
	out = str_adds(out, " "BLUE, ft_strlen(" "BLUE));
	free(line);
	line = get_folder(envp);
	out = str_adds(out, line, ft_strlen(line) - 1);
	free(line);
	free_ppl(&ppl);
	out = str_adds(out, BOLD_GREEN" 8=> "BOLD_CYAN, ft_strlen(BOLD_GREEN" 8=> "BOLD_CYAN));
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	return (out);
}
