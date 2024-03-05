/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:06:36 by jde-meo           #+#    #+#             */
/*   Updated: 2024/03/05 15:33:24 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	verify_line(char **line, int in)
{
	char	*tmp;
	
	tmp = NULL;
	if (!*line || (*line)[ft_strlen(*line) - 1] == '\n')
		return ;
	while (!*line || !tmp || (ft_strlen(*line) > 0
		&& (*line)[ft_strlen(*line) - 1] != '\n'))
	{
		dup2(g_stdin, STDIN_FILENO);
		tmp = get_next_line(in);
		if (tmp)
			*line = str_adds(*line, tmp, ft_strlen(tmp));
		free2(tmp);
	}
}

void	fill_loop(int in, int out, char *limiter, char *lmt)
{
	char	*line;
	
	line = NULL;
	while (1)
	{
		ft_printf(RED"heredoc ["BOLD_WHITE"%s"RED"] "
		GREEN"> "YELLOW, lmt);
		line = get_next_line(in);
		verify_line(&line, in);
		dup2(g_stdin, STDIN_FILENO);
		if (line == NULL)
			ft_printf("\nminishell: warning: heredoc \
delimited by end-of-file (wanted \'%s\')\n", lmt);
		if (line == NULL)
			return ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
			write(out, line, ft_strlen(line));
		free2(line);
	}
}

void	heredoc(t_pipeline **ppl, char **s, int mode)
{
	int		pipe_fd[2];
	char	*limiter;
	char	*lmt;

	(*s) += 2;
	if (mode != MODE_CMD_PRM)
		return exit_handler("Parse error, no command found", NULL, 0, 1);
	lmt = get_word(s);
	if (!lmt || *lmt == '\0')
		return exit_handler("Parse error, no limiter found", NULL, 0, 1);
	limiter = str_addc(ft_strdup(lmt), '\n');
	pipe(pipe_fd);
	get_last(*ppl)->fd_in = pipe_fd[0];
	fill_loop(STDIN_FILENO, pipe_fd[1], limiter, lmt);
	close(pipe_fd[1]);
	free2(limiter);
	free2(lmt);
}